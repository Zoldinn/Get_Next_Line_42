#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFFER_SIZE 42

typedef struct		s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_new_node(char *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

t_list	*ft_last_node(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_add_node(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new)
		return ;
	last = ft_last_node(*lst);
	if (!last)
	{
		*lst = new;
		return ;
	}
	last->next = new;
}

void	ft_free_node(t_list *lst)
{
	
}


char	*ft_gnl(int fd)
{

}

int	main(void)
{
	int			fd;
	int			read;
	static char	*buf;

	fd = open("./test", O_RDWR);
	if (fd == -1)
		return (1);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 2));
	
	close(fd);
	return (0);
}