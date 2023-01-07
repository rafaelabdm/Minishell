/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:20:15 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/12/26 15:20:15 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

// utils
void		exit_handler(t_mini *ms, const char *msg, const int code);
int			check_quotes(char c, int quotes);
char		*ft_mattstr_copy(char **mat);
char		**ft_matdup(char **mat);

// free
char		*free_ptr(char *ptr);
char		**free_mat(char **mat);
t_token		*free_token(t_token *token);

// lexer
char		**lexer(char *input);

// parser
int			parser(t_token **head, char *str);

// path
char		*find_path(char	*cmd, char **envp);

// parser_utils
void		check_pipe(char *cmd, t_token **head);

// syntax_checker
int			syntax_checker(t_mini *ms);

// expander
char		*expand(t_mini *ms, char *cmd, char **envp);
void		expander(t_mini *ms, t_token **head, char **envp);

// expander_utils
char		*get_envp(t_mini *ms, char *cmd, char **envp);

// executer
void		executor(t_mini *ms);

// executer_utils
char		**token_to_mat(t_token *token);
void		close_fds(int **fd);

// child
void		child(t_mini *ms, char **cmd, int **fd, int i);

// redirect
char		**redirect(t_mini *ms, char **cmd, int *out, int *in);

// redirect_utils
void		set_redirect(t_mini *ms, char **cmd, int *fd, char **ret);

// builtins
int			execbi(t_mini *ms, char **cmd, char ***envp, char *prompt);

// echo
void		ft_echo(t_mini *ms, char **cmd);

// cd
void		ft_cd(t_mini *ms, char **cmd, char ***envp);

// pwd
void		ft_pwd(t_mini *ms, char **cmd, char **envp);

// export
void		ft_export(t_mini *ms, char **cmd, char ***envp);

// unset
void		ft_unset(t_mini *ms, char **cmd, char ***envp);

// env
void		ft_env(t_mini *ms, char **cmd, char ***envp);

// exit
void		ft_exit(t_mini *ms, char **cmd);

#endif
