/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_init.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 12:43:02 by kehuang           #+#    #+#             */
/*   Updated: 2018/08/15 08:18:00 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INIT_H
# define FT_PRINTF_INIT_H

# include <stdarg.h>
# define PF_BUF_SIZE 4096

/*
**	format b for uint32_t base 2
**	format		:	"pdiubxXcs%"
**	flags		:	"#+ 0-"
**	modifier	:	h hh l ll
**	field
**	acc
*/

# define FLAG_SET	"#+ -0"

# define FLAG_ACC	0x200
# define FLAG_FLD	0x100

# define FLAG_ZERO	0x40
# define FLAG_MINUS	0x20
# define FLAG_PFX	0x10

# define FLAG_SPACE	0x4
# define FLAG_PLUS	0x2
# define FLAG_SHARP	0x1

# define CVT_	0x1
# define CVT_	0x1
# define CVT_	0x1
# define CVT_I	0x1
# define CVT_D	0x1

# define LCVT_ESC	0x10
# define LCVT_STRS	0x8
# define LCVT_CHARS	0x4
# define LCVT_UINTS	0x2
# define LCVT_INTS	0x1

/*
**	flags:
**	uint32	->	32bits because it will be
**			easier to add more flags if needed
**
**	____ __af _0-c _s+#
**	0000 0011 0111 0111
**
**	'f' --> boolean field
**	'a' --> boolean accuracy
**	'c'	-->	flags on/off --> "#+s" 's' refers to space character
**		prefix --> FLAG_PFX
**	'-'	-->	flag use field after
**	'0'	-->	flag use field with '0' char
*/

/*
**	converter:
**	utin16/32
**	    value|converter
**	         |
**	         |   % scud 0
**	         |       bi 1
**	         |       p  2
**	         |       x  3
**	         |       X  4
**	---- ---- ---- ----
**	0001 1111 0001 1111
**	       id
**	   X xpbu
**	        c
**	        s
**	        %
**
**	the 'converter' part will pick the function
**	the 'value' part will iter the data in the choosen function
*/

typedef enum	e_pf_modif
{
	h = 0,
	hh = 1,
	l = 2,
	ll = 3,
	none = 4
}				t_pf_modif;

typedef struct	s_buffer
{
	char	str[PF_BUF_SIZE];
	int		cur;
	int		fd;
}				t_buffer;

typedef struct	s_printf
{
	va_list			ap;
	t_buffer		buf;
	t_pf_modif		modifier;//	change to uint8
	unsigned long	fld;
	unsigned long	acc;
	unsigned int	flg;
	unsigned int	cvt;
	int				cur;
	int				n_char;
}				t_printf;
#endif
