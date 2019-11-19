/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/18 11:21:00 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/18 11:28:08 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/parse.h"

static void		pf_set_t_flags(t_flags *spec)
{
	spec->flags[0] = 0;
	spec->flags[1] = 0;
	spec->flags[2] = 0;
	spec->flags[3] = 0;
	spec->flags[4] = 0;
	spec->flags[5] = 0;
	spec->width = -1;
	spec->prec = -1;
	spec->size = 0;
	spec->conv = '0';
}

static void		pf_def_flags(char c, t_flags *spec)
{
	if (c == '#')
		spec->flags[hash] = 1;
	if (c == '0')
		spec->flags[zero] = 1;
	if (c == '-')
		spec->flags[minus] = 1;
	if (c == '+')
		spec->flags[plus] = 1;
	if (c == ' ')
		spec->flags[space] = 1;
	if (c == 'L')
		spec->flags[maj_l] = 1;
}

int				pf_mini_atoi(char **arg)
{
	int		rst;

	rst = 0;
	while (pf_isdigit(**arg))
	{
		rst *= 10;
		rst += **arg - '0';
		(*arg)++;
	}
	(*arg)--;
	return (rst);
}

static void		pf_def_size(char **arg, t_flags *spec)
{
	if (**arg == 'h' && spec->size <= hh)
	{
		spec->size = h;
		if (*(*arg + 1) == 'h')
		{
			(*arg)++;
			spec->size = hh;
		}
	}
	else if (**arg == 'l' && spec->size <= ll)
	{
		spec->size = l;
		if (*(*arg + 1) == 'l')
		{
			(*arg)++;
			spec->size = ll;
		}
	}
	else if (**arg == 'j' && spec->size <= j)
		spec->size = j;
	else if (**arg == 'z')
		spec->size = z;
}

t_flags			*pf_parse(char *arg)
{
	t_flags		*spec;

	if ((spec = (t_flags*)pf_memalloc(sizeof(*spec))) == NULL)
		return (NULL);
	pf_set_t_flags(spec);
	while (!pf_is_conv(*arg) && (*arg))
	{
		if (pf_is_flag(*arg))
			pf_def_flags(*arg, spec);
		else if (pf_isdigit(*arg))
			spec->width = pf_mini_atoi(&arg);
		else if (*arg == '.')
		{
			arg++;
			spec->prec = 0;
			spec->prec = pf_mini_atoi(&arg);
		}
		else if (pf_is_size(*arg))
			pf_def_size(&arg, spec);
		arg++;
	}
	if (!(*arg))
		return (NULL);
	spec->conv = *arg;
	return (spec);
}
