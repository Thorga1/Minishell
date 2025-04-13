#include "../../includes/minishell.h"
#include <fcntl.h>
#include <unistd.h>

// get value from t_shell env
static char *get_env_value(char *var_name, t_shell *shell)
{
    int i;
    int var_len;
    
    if (!var_name || !shell || !shell->env)
        return (NULL);
    
    // skip '$'
    if (var_name[0] == '$')
        var_name++;
    var_len = strlen(var_name);
    i = 0;
    while (shell->env[i])
    {
        // check if this line env start with the variable name and '='
        if (strncmp(shell->env[i], var_name, var_len) == 0 && 
            shell->env[i][var_len] == '=')
        {
            // return after '='
            return (shell->env[i] + var_len + 1);
        }
        i++;
    }
    return (NULL);  // no found
}

// check if a string start with '$' and is not just '$'
static int is_env_var(char *str)
{
    return (str && str[0] == '$' && str[1] != '\0');
}

// Fonction pour gérer les redirections de sortie
static int handle_output_redirection(t_smd *cmd)
{
    int original_stdout;
    int fd;
    
    // Si pas de redirection, retourner
    if (cmd->outfile == NULL)
        return (0);
        
    original_stdout = dup(STDOUT_FILENO);
    if (original_stdout == -1)
    {
        perror("Erreur lors de la duplication de STDOUT");
        return (1);
    }
    if (cmd->append)
    {
        fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
    }
    else
    {
        fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }
    if (fd == -1)
    {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        close(original_stdout);
        return (1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("Erreur lors de la redirection");
        close(fd);
        close(original_stdout);
        return (1);
    }
    
    close(fd);
    
    return (original_stdout);
}

static void restore_stdout(int original_stdout)
{
    if (original_stdout > 0)
    {
        dup2(original_stdout, STDOUT_FILENO);
        close(original_stdout);
    }
}

int ft_echo(t_smd *cmd, t_shell *shell)
{
    int print_newline = 1;
    int i = 1;  // start at 1 to skip "echo"
    char **args = cmd->args;
    int original_stdout = 0;
    int ret = 0;
    
    // Gérer la redirection de sortie
    if (cmd->outfile != NULL)
    {
        original_stdout = handle_output_redirection(cmd);
        if (original_stdout <= 0)
            return (1); // Erreur de redirection
    }
    
    if (args[i] && strcmp(args[i], "-n") == 0)
    {
        print_newline = 0;
        i++;
    }
    
    int first = 1;
    while (args[i])
    {
        if (!first)
            printf(" ");
        
        // check if the argument is an env variable
        if (is_env_var(args[i]))
        {
            char *env_value = get_env_value(args[i], shell);
            if (env_value)
                printf("%s", env_value);
            // if the variable doesn't exist, just print '\n'
        }
        else
        {
            printf("%s", args[i]);
        }
        
        first = 0;
        i++;
    }
    
    if (print_newline)
        printf("\n");
    
    // Restaurer la sortie standard si nécessaire
    if (cmd->outfile != NULL)
    {
        restore_stdout(original_stdout);
    }
    
    return (ret);
}
