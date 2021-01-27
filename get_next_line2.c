#include "get_next_line.h"

char *find_newline(char *str)
{
	char *trimmed_str;
	char *index;
	
	if (!str)
		return (NULL);
	index = ft_strchr(str, '\n');
	if (index)
	{
		trimmed_str = ft_substr(str, 0, index - str);	
	}
	else
		return (NULL);
	return (trimmed_str);
}

char *save_remaining(char *str)
{
	char *remaining_str;

	if (!str)
		return (NULL);
	remaining_str = ft_strchr(str, '\n');
	if (remaining_str)
		remaining_str += 1;
	return (remaining_str);
}

int	get_next_line(int fd, char **line)
{
	char buff[BUFFER_SIZE + 1];
	static char *temp;
	char *str;
	char *nl_str;
	int ret;
	static int i;

	printf("---------\n%d\n\n", i);
	i += 1;

	if (temp)
	{
		if ((*line = find_newline(temp)))
		{
			temp = save_remaining(temp);
			ret = 1;
		}
		else
		{
			ret = read(fd, buff, BUFFER_SIZE);
			buff[ret] = '\0';
			str = ft_substr(buff, 0, ret);
			if ((nl_str = find_newline(str)))
			{
				*line = ft_strjoin(temp, nl_str);
				temp = save_remaining(str);
			}
			else
			{
				*line = ft_strjoin(temp, str);
				temp = NULL;
			}
		}
	}
	else
	{
		ret = read(fd, buff, BUFFER_SIZE);
		buff[ret] = '\0';
		str = ft_substr(buff, 0, ret);
		if ((*line = find_newline(str)))
			temp = save_remaining(str);
		else
			*line = str;
	}
	if (ret > 0)
		return (1);
	else if (ret == 0)
		return (0);
	else
		return (-1);
}

int main()
{
	char *str;
	int fd;
	int ret;

	str = NULL;
	fd = open("prout", O_RDONLY);
	ret = get_next_line(fd, &str);
	printf("*line: |%s|\n\n", str);
	while (ret > 0)
	{
		ret = get_next_line(fd, &str);
		printf("*line: |%s|\n\n", str);
	}
	return (0);
}