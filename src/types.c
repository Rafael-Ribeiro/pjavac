#define TYPES_C

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "inc/structures.h"
#include "inc/utils.h"
#include "inc/types.h"
#include "inc/insert.h"
#include "inc/free.h"

is_type_native operators_binary[MAX_OPERATORS_BINARY][MAX_NATIVE_TYPES-1][MAX_NATIVE_TYPES-1] =
{
	/* t_assign_op_* */
	/* t_assign_op_eq (=) */
	{
		/*					bool						, byte					, char					, double				, float					, int					, long					, short					, String					<- second operand */
		/*	bool	=	*/	{	t_type_native_bool		, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	=	*/	{	ERROR					, t_type_native_byte	, t_type_native_byte	, t_type_native_byte	, t_type_native_byte	, t_type_native_byte	, t_type_native_byte	, t_type_native_byte	, ERROR					},
		/*	char	=	*/	{	ERROR					, t_type_native_char	, t_type_native_char	, ERROR					, ERROR					, t_type_native_char	, t_type_native_char	, t_type_native_char	, ERROR					},
		/*	double	=	*/	{	ERROR					, ERROR					, ERROR					, t_type_native_double	, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	=	*/	{	ERROR					, t_type_native_float	, t_type_native_float	, t_type_native_float	, t_type_native_float	, t_type_native_float	, t_type_native_float	, t_type_native_float	, ERROR					},
		/*	int		=	*/	{	ERROR					, t_type_native_int		, t_type_native_int		, ERROR					, ERROR					, t_type_native_int		, t_type_native_int		, t_type_native_int		, ERROR					},
		/*	long	=	*/	{	ERROR					, t_type_native_long	, t_type_native_long	, ERROR					, ERROR					, t_type_native_long	, t_type_native_long	, t_type_native_long	, ERROR					},
		/*	short	=	*/	{	ERROR					, t_type_native_short	, t_type_native_short	, ERROR					, ERROR					, t_type_native_short	, t_type_native_short	, t_type_native_short	, ERROR					},
		/*	String	=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, t_type_native_string	}
	},

	/* t_assign_op_shift_r_eq (>>=) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	>>=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	>>=	*/	{	ERROR					, t_type_native_byte	, t_type_native_byte	, ERROR					, ERROR					, t_type_native_byte	, t_type_native_byte	, t_type_native_byte	, ERROR					},
		/*	char	>>=	*/	{	ERROR					, t_type_native_char	, t_type_native_char	, ERROR					, ERROR					, t_type_native_char	, t_type_native_char	, t_type_native_char	, ERROR					},
		/*	double	>>=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	>>=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		>>=	*/	{	ERROR					, t_type_native_int		, t_type_native_int		, ERROR					, ERROR					, t_type_native_int		, t_type_native_int		, t_type_native_int		, ERROR					},
		/*	long	>>=	*/	{	ERROR					, t_type_native_long	, t_type_native_long	, ERROR					, ERROR					, t_type_native_long	, t_type_native_long	, t_type_native_long	, ERROR					},
		/*	short	>>=	*/	{	ERROR					, t_type_native_short	, t_type_native_short	, ERROR					, ERROR					, t_type_native_short	, t_type_native_short	, t_type_native_short	, ERROR					},
		/*	String	>>=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* t_assign_op_shift_l_eq (<<=) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	>>=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	>>=	*/	{	ERROR					, t_type_native_byte	, t_type_native_byte	, ERROR					, ERROR					, t_type_native_byte	, t_type_native_byte	, t_type_native_byte	, ERROR					},
		/*	char	>>=	*/	{	ERROR					, t_type_native_char	, t_type_native_char	, ERROR					, ERROR					, t_type_native_char	, t_type_native_char	, t_type_native_char	, ERROR					},
		/*	double	>>=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	>>=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		>>=	*/	{	ERROR					, t_type_native_int		, t_type_native_int		, ERROR					, ERROR					, t_type_native_int		, t_type_native_int		, t_type_native_int		, ERROR					},
		/*	long	>>=	*/	{	ERROR					, t_type_native_long	, t_type_native_long	, ERROR					, ERROR					, t_type_native_long	, t_type_native_long	, t_type_native_long	, ERROR					},
		/*	short	>>=	*/	{	ERROR					, t_type_native_short	, t_type_native_short	, ERROR					, ERROR					, t_type_native_short	, t_type_native_short	, t_type_native_short	, ERROR					},
		/*	String	>>=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_assign_op_add_eq (+=) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	+=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	+=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	+=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	+=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	+=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		+=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	+=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	+=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	+=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_assign_op_sub_eq (-=) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	-=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	-=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	-=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	-=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	-=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		-=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	-=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	-=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	-=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_assign_op_mul_eq (*=) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	*=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	*=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	*=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	*=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	*=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		*=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	*=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	*=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	*=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_assign_op_div_eq (/=) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	/=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	/=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	/=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	/=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	/=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		/=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	/=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	/=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	/=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_assign_op_mod_eq (%=) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	%=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	%=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	%=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	%=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	%=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		%=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	%=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	%=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	%=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_assign_op_and_eq (&=) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	&=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	&=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	&=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	&=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	&=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		&=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	&=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	&=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	&=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_assign_op_xor_eq (^=) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	^=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	^=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	^=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	^=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	^=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		^=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	^=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	^=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	^=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_assign_op_or_eq (|=) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	|=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	|=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	|=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	|=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	|=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		|=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	|=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	|=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	|=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* t_binary_op_* */
	/* t_binary_op_add (+) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	+	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, t_type_native_string	},
		/*	byte	+	*/	{	ERROR					, t_type_native_int		, t_type_native_int		, t_type_native_double	, t_type_native_float	, t_type_native_int		, t_type_native_long	, t_type_native_int		, t_type_native_string	},
		/*	char	+	*/	{	ERROR					, t_type_native_int		, t_type_native_int		, t_type_native_double	, t_type_native_float	, t_type_native_int		, t_type_native_long	, t_type_native_int		, t_type_native_string	},
		/*	double	+	*/	{	ERROR					, t_type_native_float	, t_type_native_float	, t_type_native_double	, t_type_native_double	, t_type_native_double	, t_type_native_double	, t_type_native_double	, t_type_native_string	},
		/*	float	+	*/	{	ERROR					, t_type_native_float	, t_type_native_float	, t_type_native_double	, t_type_native_float	, t_type_native_float	, t_type_native_float	, t_type_native_float	, t_type_native_string	},
		/*	int		+	*/	{	ERROR					, t_type_native_int		, t_type_native_int		, t_type_native_double	, t_type_native_float	, t_type_native_int		, t_type_native_long	, t_type_native_int		, t_type_native_string	},
		/*	long	+	*/	{	ERROR					, t_type_native_long	, t_type_native_long	, t_type_native_double	, t_type_native_float	, t_type_native_long	, t_type_native_long	, t_type_native_long	, t_type_native_string	},
		/*	short	+	*/	{	ERROR					, t_type_native_int		, t_type_native_int		, t_type_native_double	, ERROR					, t_type_native_int		, t_type_native_long	, t_type_native_int		, t_type_native_string	},
		/*	String	+	*/	{	t_type_native_string	, t_type_native_string	, t_type_native_string	, t_type_native_string	, t_type_native_string	, t_type_native_string	, t_type_native_string	, t_type_native_string	, t_type_native_string	}
	},

	/* t_binary_op_sub (-) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	-	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	-	*/	{	ERROR					, t_type_native_int		, t_type_native_int		, t_type_native_double	, t_type_native_float	, t_type_native_int		, t_type_native_long	, t_type_native_int		, ERROR					},
		/*	char	-	*/	{	ERROR					, t_type_native_int		, t_type_native_int		, t_type_native_double	, t_type_native_float	, t_type_native_int		, t_type_native_long	, t_type_native_int		, ERROR					},
		/*	double	-	*/	{	ERROR					, t_type_native_float	, t_type_native_float	, t_type_native_double	, t_type_native_double	, t_type_native_double	, t_type_native_double	, t_type_native_double	, ERROR					},
		/*	float	-	*/	{	ERROR					, t_type_native_float	, t_type_native_float	, t_type_native_double	, t_type_native_float	, t_type_native_float	, t_type_native_float	, t_type_native_float	, ERROR					},
		/*	int		-	*/	{	ERROR					, t_type_native_int		, t_type_native_int		, t_type_native_double	, t_type_native_float	, t_type_native_int		, t_type_native_long	, t_type_native_int		, ERROR					},
		/*	long	-	*/	{	ERROR					, t_type_native_long	, t_type_native_long	, t_type_native_double	, t_type_native_float	, t_type_native_long	, t_type_native_long	, t_type_native_long	, ERROR					},
		/*	short	-	*/	{	ERROR					, t_type_native_int		, t_type_native_int		, t_type_native_double	, ERROR					, t_type_native_int		, t_type_native_long	, t_type_native_int		, ERROR					},
		/*	String	-	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_binary_op_mul (*) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	*	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	*	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	*	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	*	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	*	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		*	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	*	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	*	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	*	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_binary_op_div (/) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	/	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	/	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	/	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	/	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	/	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		/	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	/	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	/	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	/	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_binary_op_mod (%) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	%	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	%	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	%	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	%	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	%	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		%	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	%	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	%	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	%	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_binary_op_and (&) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	&	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	&	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	&	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	&	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	&	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		&	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	&	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	&	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	&	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_binary_op_or (|) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	|	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	|	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	|	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	|	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	|	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		|	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	|	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	|	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	|	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_binary_op_xor (^) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	^	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	^	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	^	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	^	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	^	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		^	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	^	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	^	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	^	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_binary_op_shift_r (>>) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	>>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	>>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	>>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	>>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	>>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		>>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	>>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	>>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	>>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_binary_op_shift_l (<<) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	<<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	<<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	<<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	<<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	<<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		<<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	<<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	<<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	<<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* t_binary_op_logic_and (&&) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	&&	*/	{	t_type_native_bool		, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	&&	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	&&	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	&&	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	&&	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		&&	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	&&	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	&&	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	&&	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* t_binary_op_logic_or */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	||	*/	{	t_type_native_bool		, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	||	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	||	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	||	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	||	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		||	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	||	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	||	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	||	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* t_binary_op_* (the equality ones) */
	/* FIXME/TODO: t_binary_op_eq (==) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	==	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	==	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	==	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	==	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	==	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		==	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	==	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	==	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	==	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_binary_op_ne (!=) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	!=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	!=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	!=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	!=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	!=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		!=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	!=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	!=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	!=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_binary_op_l (<) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	<	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_binary_op_g (>) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	>	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_binary_op_le (<=) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	<=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	<=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	<=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	<=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	<=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		<=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	<=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	<=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	<=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_binary_op_ge (>=) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	>=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	>=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	char	>=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	double	>=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	float	>=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	int		>=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	long	>=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	short	>=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	String	>=	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* t_binary_op_eq3 (===) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	===	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	},
		/*	byte	===	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	},
		/*	char	===	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	},
		/*	double	===	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	},
		/*	float	===	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	},
		/*	int		===	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	},
		/*	long	===	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	},
		/*	short	===	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	},
		/*	String	===	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	}
	},

	/* t_binary_op_ne3 (!==) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	!==	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	},
		/*	byte	!==	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	},
		/*	char	!==	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	},
		/*	double	!==	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	},
		/*	float	!==	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	},
		/*	int		!==	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	},
		/*	long	!==	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	},
		/*	short	!==	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	},
		/*	String	!==	*/	{	t_type_native_bool		, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	, t_type_native_bool	}
	}
};

is_type_native operators_unary[MAX_OPERATORS_UNARY][MAX_NATIVE_TYPES-1] =
{
	/* FIXME/TODO: t_unary_op_operator_plus (pre ++ / pos ++) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	++bool++	*/	ERROR,
		/*	++byte++	*/	ERROR,
		/*	++char++	*/	ERROR,
		/*	++double++	*/	ERROR,
		/*	++float++	*/	ERROR,
		/*	++int++		*/	ERROR,
		/*	++long++	*/	ERROR,
		/*	++short++	*/	ERROR,
		/*	++String++	*/	ERROR,
	},

	/* FIXME/TODO: t_unary_op_operator_minus (pre -- / pos --) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	--bool--	*/	ERROR,
		/*	--byte--	*/	ERROR,
		/*	--char--	*/	ERROR,
		/*	--double--	*/	ERROR,
		/*	--float--	*/	ERROR,
		/*	--int--		*/	ERROR,
		/*	--long--	*/	ERROR,
		/*	--short--	*/	ERROR,
		/*	--String--	*/	ERROR,
	},

	/* FIXME/TODO: t_unary_op_operator_not (!) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	!bool		*/	ERROR,
		/*	!byte		*/	ERROR,
		/*	!char		*/	ERROR,
		/*	!double		*/	ERROR,
		/*	!float		*/	ERROR,
		/*	!int		*/	ERROR,
		/*	!long		*/	ERROR,
		/*	!short		*/	ERROR,
		/*	!String		*/	ERROR,
	},

	/* FIXME/TODO: t_unary_op_operator_bin_not (~) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	~bool		*/	ERROR,
		/*	~byte		*/	ERROR,
		/*	~char		*/	ERROR,
		/*	~double		*/	ERROR,
		/*	~float		*/	ERROR,
		/*	~int		*/	ERROR,
		/*	~long		*/	ERROR,
		/*	~short		*/	ERROR,
		/*	~String		*/	ERROR
	}
};

char *string_type_native(is_type_native* type)
{
	char strings[][8] = { "boolean", "byte", "char", "double", "float", "int", "long", "short", "string", "void"};
	return __strdup(strings[*type]);
}

char *string_type_decl(is_type_decl* type)
{
	if (type->type != t_type_decl_type_object)
		return string_type_native(&type->data.type_object->type);

	return string_array_decl(type->data.array);
}

char *string_array_decl(is_array_decl* array)
{
	char *native, *val;
	int size, i;

	native = string_type_native(&array->type->type);
	size = strlen(native) + 2*(array->dims->size)+1;

	val = (char*)malloc(sizeof(char)*size);
	strcpy(val, native); 
	
	for (i = 0; i < array->dims->size; i++)
		strcat(val, "[]");

	free(native);
	return val;
}

bool type_native_assign_able(is_type_native native, is_type_decl* s_type)
{
	if (s_type->type != t_type_decl_type_object)
		return false;

	return operators_binary[t_assign_op_eq][native][s_type->data.type_object->type] != ERROR;
}

bool type_type_assign_able(is_type_decl* s_type, is_type_decl* s_type2)
{
	/* TODO */
	return false;
}

bool type_type_cast_able(is_type_decl* s_type, is_type_decl* s_type2)
{
	/*
		FIXME:
		this is invalid if we allow objects:
		e.g. 	Integer b[] = (Integer[])(new Object[1]); is valid BUT
				int b[] = (float[])(new int[1]) is NOT
	*/
	if (s_type->type == t_type_decl_array_decl)
		return false;

	if ((s_type->data.type_object->type == t_type_native_bool || s_type->data.type_object->type == t_type_native_string)
		&& s_type->data.type_object->type != s_type2->data.type_object->type)
		return false;

	return true;
}

bool type_var_init_assign_able(is_type_decl *type, int nDimensions, is_var_initializer *init)
{
	is_var_initializer_list *it;
	is_type_decl *dupType;

	if (nDimensions)
	{
		/* line no will be ignored */
		/* assuming type is is_array_decl, since nDimensions != 0; check if valid */
		dupType = insert_type_decl_array(insert_array_decl (insert_type_object(type->data.array->type->type), new_dims_empty_list(0, nDimensions)));
	} else
	{
		if (type->type == t_type_decl_array_decl)
			/* type is an array but no nDimensions: convert the type_decl to t_type_decl_type_object */
			dupType = insert_type_decl_object(insert_type_object(type->data.array->type->type));
		else
			dupType = insert_type_decl_object(insert_type_object(type->data.type_object->type));

	}

	switch (init->type)
	{
		case t_var_initializer_val_arr:
			if (init->data.array == NULL) /* { } */
				return (nDimensions == 1); /* valid if nDimensions is 1 */

			for (it = init->data.array; it != NULL; it = it->next)
			{
				if(!type_var_init_assign_able(dupType, (nDimensions ? nDimensions - 1 : 0), it->node) /* FIXME: is type_type_assign_able() call also needed? */)
				{
					free_type_decl(dupType);
					return false;
				}
			}

			/*
			 * init->data.array is never NULL;
			 * duplicate type_decl of the first var_initializer and update "parent" var_initializer	
			 */
			init->s_type = duplicate_type_decl(init->data.array->node->s_type);
		break;
		case t_var_initializer_expr:
			if (type_type_assign_able(dupType, init->data.expr->s_type))
				/* propagate s_type to var_initializer */
				init->s_type = init->data.expr->s_type;
			else
			{
				free_type_decl(dupType);
				return false;
			}
		break;
	}

	free_type_decl(dupType);

	return true;
}
