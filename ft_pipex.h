#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define INFILE 0
# define OUTFILE 1

int	ft_str_ncmp (char *str1, char *str2, int n);
int	ft_pchr (char *str, char c);
char	*ft_str_ndup (char *str, unsigned int n);
char	*path_join (char *path, char *bin);
char	**ft_str_split (char *str, char div);

#endif 