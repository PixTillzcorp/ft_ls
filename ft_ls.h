#ifndef FT_LS_H
# define FT_LS_H

# include <uuid/uuid.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>
# include "libft/libft.h"

typedef	struct	dirent
				s_dir;
typedef	struct	stat
				s_stat;
typedef	struct	passwd
				s_pwd;
typedef	struct	group
				s_grp;

int				ft_closedir(DIR *op_dir);
int				ft_isdir(const char *path);
int				ft_nbrfile(const char *path, int a);
DIR				*ft_opendir(const char *path);

void			ft_error(const char *msg, int usage);
void			ft_perror(const char *msg);

int				ft_flag(const char **args, char **flag);
int				ft_disp_dir(const char *path, char *flags, int multi);
void			ft_print_sort(char **tab, char *flags);
void			ft_print_large(const char *path, int *mlen);
int				ft_print_single(const char *path, int large);

long			ft_data_mtime(const char *path);
char			*ft_data_date(const char *path);
char			*ft_data_wrx(const char *path);
char			*ft_data_name(const char *path);
int				ft_data_nlink(const char *path);
char			*ft_data_uid(const char *path, int len);
char			*ft_data_gid(const char *path, int len);
char			*ft_data_size(const char *path, int len);

char			**ft_init_tab(int size);
char			**ft_put_in_tab(char **tab, const char *path, char *name);
char			*ft_newpath(char *dest, const char *p, const char* d);
void			ft_free_tab(char **tab);
char			**ft_sort_tab(char **tab, char *flags);

#endif
