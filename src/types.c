#define TYPES_C

#include <stdbool.h>

#include "inc/structures.h"
#include "inc/types.h"

is_type_native operators_native[MAX_OPERATORS][MAX_NATIVE_TYPES-1][MAX_NATIVE_TYPES-1] =
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
		/*	byte	+	*/	{	ERROR					, t_type_native_byte	, t_type_native_int		, t_type_native_double	, t_type_native_float	, t_type_native_int		, t_type_native_long	, t_type_native_int		, t_type_native_string	},
		/*	char	+	*/	{	ERROR					, t_type_native_int		, t_type_native_char	, t_type_native_double	, t_type_native_float	, t_type_native_int		, t_type_native_long	, t_type_native_int		, t_type_native_string	},
		/*	double	+	*/	{	ERROR					, t_type_native_float	, t_type_native_float	, t_type_native_double	, t_type_native_double	, t_type_native_double	, t_type_native_double	, t_type_native_double	, t_type_native_string	},
		/*	float	+	*/	{	ERROR					, t_type_native_float	, t_type_native_float	, t_type_native_double	, t_type_native_float	, t_type_native_float	, t_type_native_float	, t_type_native_float	, t_type_native_string	},
		/*	int		+	*/	{	ERROR					, t_type_native_int		, t_type_native_int		, t_type_native_double	, t_type_native_float	, t_type_native_int		, t_type_native_long	, t_type_native_int		, t_type_native_string	},
		/*	long	+	*/	{	ERROR					, t_type_native_long	, t_type_native_long	, t_type_native_double	, t_type_native_float	, t_type_native_long	, t_type_native_long	, t_type_native_long	, t_type_native_string	},
		/*	short	+	*/	{	ERROR					, t_type_native_int		, t_type_native_int		, t_type_native_double	, ERROR					, t_type_native_int		, t_type_native_long	, t_type_native_short	, t_type_native_string	},
		/*	String	+	*/	{	t_type_native_string	, t_type_native_string	, t_type_native_string	, t_type_native_string	, t_type_native_string	, t_type_native_string	, t_type_native_string	, t_type_native_string	, t_type_native_string	}
	},

	/* t_binary_op_sub (-) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	bool	-	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	byte	-	*/	{	ERROR					, t_type_native_byte	, t_type_native_int		, t_type_native_double	, t_type_native_float	, t_type_native_int		, t_type_native_long	, t_type_native_int		, ERROR					},
		/*	char	-	*/	{	ERROR					, t_type_native_int		, t_type_native_char	, t_type_native_double	, t_type_native_float	, t_type_native_int		, t_type_native_long	, t_type_native_int		, ERROR					},
		/*	double	-	*/	{	ERROR					, t_type_native_float	, t_type_native_float	, t_type_native_double	, t_type_native_double	, t_type_native_double	, t_type_native_double	, t_type_native_double	, ERROR					},
		/*	float	-	*/	{	ERROR					, t_type_native_float	, t_type_native_float	, t_type_native_double	, t_type_native_float	, t_type_native_float	, t_type_native_float	, t_type_native_float	, ERROR					},
		/*	int		-	*/	{	ERROR					, t_type_native_int		, t_type_native_int		, t_type_native_double	, t_type_native_float	, t_type_native_int		, t_type_native_long	, t_type_native_int		, ERROR					},
		/*	long	-	*/	{	ERROR					, t_type_native_long	, t_type_native_long	, t_type_native_double	, t_type_native_float	, t_type_native_long	, t_type_native_long	, t_type_native_long	, ERROR					},
		/*	short	-	*/	{	ERROR					, t_type_native_int		, t_type_native_int		, t_type_native_double	, ERROR					, t_type_native_int		, t_type_native_long	, t_type_native_short	, ERROR					},
		/*	String	-	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	}

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
	},

	/* FIXME/TODO: t_unary_op_operator_plus (pre ++ / pos ++) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	++bool++	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	++byte++	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	++char++	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	++double++	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	++float++	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	++int++		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	++long++	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	++short++	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	++String++	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_unary_op_operator_minus (pre -- / pos --) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	--bool--	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	--byte--	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	--char--	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	--double--	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	--float--	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	--int--		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	--long--	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	--short--	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	--String--	*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_unary_op_operator_not (!) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	!bool		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	!byte		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	!char		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	!double		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	!float		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	!int		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	!long		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	!short		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	!String		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	},

	/* FIXME/TODO: t_unary_op_operator_bin_not (~) */
	{
		/*						bool					, byte					, char					, double				, float					, int					, long					, short					, String					<- first operand */
		/*	~bool		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	~byte		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	~char		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	~double		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	~float		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	~int		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	~long		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	~short		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					},
		/*	~String		*/	{	ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					, ERROR					}
	}
};
