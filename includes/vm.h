/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frenna <frenna@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:12:49 by fwiley            #+#    #+#             */
/*   Updated: 2020/06/30 07:55:53 by fwiley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "op.h"
# include "../libft/includes/libft.h"
# include "types.h"

# define OP_CODE_LEN	1
# define ARG_CODE_LEN	1

# define FLAG_DUMP_LEN	32
# define FLAG_D_LEN		64

/*
********************************************************************************
** >>> Colors for trace output <<<
********************************************************************************
*/

# define YEL			"\033[33m"
# define EOC			"\033[0m"

/*
********************************************************************************
** >>> ERROR CODE <<<
********************************************************************************
*/

enum {USAGE, L_SIZE, M_SIZE, ERR_FLAG, ERR_FILE, ERR_MANY, ERR_MALLOC, ERR_DS};

/*
********************************************************************************
** >>> FLAGS <<<<
**
**   -dump [NBR_CYCLE]		# 0b 0000 0001
** At the end of NBR_CYCLE of executions, dump the memory on the standard
** output and quit the game
**
**   -aff					# 0b 0000 0010
** Display ASCII value on standard output during aff() operation
**
**   -visual				# 0b 0000 0100
** Includes a visual mode. on each cycle memory and game parameters
** will be displayed
**
**   -debug					# ob 0000 1000
** Print process movement, operation name, arguments
**
**   -fun					# ob 0001 0000
** All operations waiting 5 cycles and execute
********************************************************************************
*/

# define DUMP			(1)
# define AFF			(1 << 1)
# define VISUAL			(1 << 2)
# define DEBUG			(1 << 3)
# define FUN			(1 << 4)

# define DEBUG_LIVES	(1)
# define DEBUG_CYCLES	(1 << 1)
# define DEBUG_OP		(1 << 2)
# define DEBUG_DEATH	(1 << 3)
# define DEBUG_PC		(1 << 4)

/*
********************************************************************************
** >>> Player <<<
**
**   DESCRIPTION
** The "Player" structure contains information about the player. The "Player"
** and the "Process" are not related to each other.
**
**   .id
** ID of player
**
**   .name
** Name of player
**
**   .comment
** Comment of player
**
**   .executable_code
** Executable code of player
**
** .code_size
** Size of executable code of player
**
**   .alive				# unsigned 1 byte
** Flag indicating whether the player is alive. 1 - alive, 0 - die
********************************************************************************
*/

typedef struct			s_player
{
	size_t				id;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	t_uint8				executable_code[CHAMP_MAX_SIZE];
	t_int32				code_size;
	t_uint8				alive;
}						t_player;

void					init_player(t_player *new, size_t id, char *name,
						char *comment);

void					clear_player(t_player *player);

void					copy_player(t_player *from, t_player *to);

/*
********************************************************************************
** >>> Visual map <<<
*/

typedef struct			s_vs_map
{
	t_uint32			id;
	t_uint8				value;
}						t_vs_map;

/*
********************************************************************************
** >>> Game <<<
**
**   DESCRIPTION
** The "Game" structure contains the battlefield and the main parameters
** about the game
**
**   .cycle
** Counter containing total cycles have passed since the start of the game
**
**   .cycle_to_check
** Counter containing the number of cycles left before the check
**
**   .cycle_ to_die
** The number of cycles between checks
**
**   .nbr_live_check
** Counter the number of "live" operations since the last check
**
**   .nbr_check
** Counter the number of checks performed with the same "cycle_to_die"
**
**   .flags
** Information about flags -dump -aff -visual
** See also >>> FLAGS <<<
**
**   .dump_nbr
** At the end of "dump" of executions, dump the memory on the standard
** output and quit the game
**
**   .last_live_player
** The player who was last told that he was alive
**
**   .map
** Stored battlefield
**
**   .map_mask
** Additional information is stored for the battlefield,
** necessary for the visual mode
**
**   .player
** Contains a list of players in an array. See also >>> Player <<<
********************************************************************************
*/

typedef struct			s_game
{
	t_uint32			cycle;
	t_int32				cycle_to_check;
	t_int32				cycle_to_die;
	t_uint32			nbr_live_op;
	t_uint32			nbr_check;
	t_uint8				flags;
	size_t				dump_nbr;
	size_t				dump_len;
	t_int32				debug_nbr;
	t_uint32			last_live_player;
	t_uint8				map[MEM_SIZE];
	t_vs_map			map_vs[MEM_SIZE];
	t_player			players[MAX_PLAYERS + 1];
}						t_game;

t_game					init_game();

/*
********************************************************************************
** >>> Process <<<    also known as "Karetka"
**
**   DESCRIPTION
** The "Process" structure is a doubly linked list. Contains information about
** the process on the map
**
**   .registries
** Array of variables for storing data
**
**   .carry
** A special variable that affects the operation of the "zjmp" function and can
** take one of two values: 1 or 0. If it's 1, then the function updates the
** "position"
**
**   .position
** Map address. See also >>> Game <<<, game.map
**
**   .op_code
** Contains the operation code, at the time of moving to this position on the
** map. See also >>> Operations <<<
**
**   .cycle_to_exe
** A counter containing the number of cycles that the carriage must wait before
** starting an operation.
**
**   .live_last_cycle
** Contains the cycle on which the last "live" operation was performed
**
**   .id
** Index of process
**
**   .next
** Next process
**
**   .prev
** Previous process
********************************************************************************
*/

typedef struct			s_process
{
	t_int32				reg[REG_NUMBER + 1];
	t_uint8				carry;
	t_uint32			pos;
	t_uint8				op_code;
	t_uint32			next_pos;
	t_uint32			cycle_to_exe;
	t_uint32			live_last_cycle;
	t_uint32			live_last_id;
	t_uint32			id;
	t_uint32			player_id;
	struct s_process	*next;
	struct s_process	*prev;
}						t_process;

t_process				*init_process(t_int32 r1);

void					remove_one_process(t_process **list);

void					remove_process(t_process **list);

t_uint8					add_process(t_process **process, t_int32 reg_value);

t_process				*get_last_process(t_process *first);

t_process				*get_first_process(t_process *last);

t_process				*copy_process(t_process *src, t_process *prev,
						t_uint32 position);

/*
********************************************************************************
** >>> Parse arguments <<<
********************************************************************************
*/

void					parse_flags(char ***arg_val, int *arg_count,
						t_player players[], t_game *game);

void					parse_file(char *file_name, t_player players[],
						size_t id);

void					parse_args(int ac, char **av, t_game *game);

void					put_error(int error, char *s);

/*
********************************************************************************
** >>> Execute <<<
********************************************************************************
*/

void					check_game(t_process **process, t_game *game);

void					execute_process(t_process *process, t_game *game);

void					run_game(t_game *game);

/*
********************************************************************************
** >>> Print functions <<<
********************************************************************************
*/

void					print_hello(t_process *process, t_game *game);

void					print_winner(t_game *game);

void					print_map(t_game *game);

void					print_next_position(t_process process, t_game game);

void					print_op(t_process process);

void					print_load_op(t_process process, t_game game);

/*
********************************************************************************
** >>> Staff functions <<<
********************************************************************************
*/

t_uint32				crop_index(t_int32 address);

t_uint32				crop_index_u(t_uint32 address);

#endif
