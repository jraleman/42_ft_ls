#include "ft_ls.h"

/*
** ...
*/

static int	is_dir(char *path)
{
	DIR		*dir;

	if (!(dir = opendir(path)))
		return (!ft_strcmp("Not a directory", strerror(errno)) ? 0 : -1);
	return (!closedir(dir) ? 1 : -1);
}

/*
** ...
*/

static int 	check_dir(char *path, char *opt)
{
	int			ret;
	struct stat stt;

	if ((ret = is_dir(path)) > 0)
	{
		if (ft_cisin(opt, 'l') && path[ft_strlen(path) - 1] != '/')
		{
			lstat(path, &stt);
			if (S_ISLNK(stt.st_mode))
				ret = 2;
		}
	}
	if (ret == -1)
		ft_dprintf(2, "ls: %s: %s\n", path, strerror(errno));
	return (ret == 0 ? 2 : ret);
}

/*
** ...
*/

t_path	*path_add(t_path *path, char *dir, char *opt)
{
	t_path *last;
	t_path *tmp;

	if (!(last = malloc(sizeof(t_path))))
		return (NULL);
	last->error = check_dir(dir, opt);
	last->name = ft_strdup(dir);
	last->next = NULL;
	if (!path)
		return (last);
	tmp = path;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = last;
	return (path);
}