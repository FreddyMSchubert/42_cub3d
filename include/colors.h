/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:38:30 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/21 07:36:06 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

// Regular text
# define ANSI_COLOR_BLACK "\x1b[30m"
# define ANSI_COLOR_RED "\x1b[31m"
# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_YELLOW "\x1b[33m"
# define ANSI_COLOR_BLUE "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN "\x1b[36m"
# define ANSI_COLOR_WHITE "\x1b[37m"

// Bold text
# define ANSI_BOLD_BLACK "\x1b[1;30m"
# define ANSI_BOLD_RED "\x1b[1;31m"
# define ANSI_BOLD_GREEN "\x1b[1;32m"
# define ANSI_BOLD_YELLOW "\x1b[1;33m"
# define ANSI_BOLD_BLUE "\x1b[1;34m"
# define ANSI_BOLD_MAGENTA "\x1b[1;35m"
# define ANSI_BOLD_CYAN "\x1b[1;36m"
# define ANSI_BOLD_WHITE "\x1b[1;37m"

// Dim text
# define ANSI_DIM_BLACK "\x1b[2;30m"
# define ANSI_DIM_RED "\x1b[2;31m"
# define ANSI_DIM_GREEN "\x1b[2;32m"
# define ANSI_DIM_YELLOW "\x1b[2;33m"
# define ANSI_DIM_BLUE "\x1b[2;34m"
# define ANSI_DIM_MAGENTA "\x1b[2;35m"
# define ANSI_DIM_CYAN "\x1b[2;36m"
# define ANSI_DIM_WHITE "\x1b[2;37m"

// Italic text
# define ANSI_ITALIC_BLACK "\x1b[3;30m"
# define ANSI_ITALIC_RED "\x1b[3;31m"
# define ANSI_ITALIC_GREEN "\x1b[3;32m"
# define ANSI_ITALIC_YELLOW "\x1b[3;33m"
# define ANSI_ITALIC_BLUE "\x1b[3;34m"
# define ANSI_ITALIC_MAGENTA "\x1b[3;35m"
# define ANSI_ITALIC_CYAN "\x1b[3;36m"
# define ANSI_ITALIC_WHITE "\x1b[3;37m"

// Underline
# define ANSI_UNDERLINE_BLACK "\x1b[4;30m"
# define ANSI_UNDERLINE_RED "\x1b[4;31m"
# define ANSI_UNDERLINE_GREEN "\x1b[4;32m"
# define ANSI_UNDERLINE_YELLOW "\x1b[4;33m"
# define ANSI_UNDERLINE_BLUE "\x1b[4;34m"
# define ANSI_UNDERLINE_MAGENTA "\x1b[4;35m"
# define ANSI_UNDERLINE_CYAN "\x1b[4;36m"
# define ANSI_UNDERLINE_WHITE "\x1b[4;37m"

// Background
# define ANSI_BACKGROUND_BLACK "\x1b[40m"
# define ANSI_BACKGROUND_RED "\x1b[41m"
# define ANSI_BACKGROUND_GREEN "\x1b[42m"
# define ANSI_BACKGROUND_YELLOW "\x1b[43m"
# define ANSI_BACKGROUND_BLUE "\x1b[44m"
# define ANSI_BACKGROUND_MAGENTA "\x1b[45m"
# define ANSI_BACKGROUND_CYAN "\x1b[46m"
# define ANSI_BACKGROUND_WHITE "\x1b[47m"

// Additional styles
# define ANSI_HIDDEN "\x1b[8m"
# define ANSI_STRIKETHROUGH "\x1b[9m"

// Reset
# define ANSI_RESET "\x1b[0m"

#endif