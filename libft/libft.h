/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 01:28:36 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/12/28 18:19:51 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// struct va_list
// va_end()
// va_start()
# include <stdarg.h>

// malloc()
# include <stdlib.h>

// write ()
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

///
/// The members of the t_list struct are:
///
///• content: The data contained in the node.
///• next: The address of the next node, or NULL if the next node is the last
/// one.
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/**
 * @brief [library] ctype.h •
 * Check whether 'c' is a valid ASCII alphabetic character (i.e., 65 ('A') to 90
 * ('Z') or 97 ('a') to 122 ('z')).
 * 
 * @param c Character as an integer.
 * @return Return 1024 if the character 'c' is an alphabetic character, and a 0
 * if not.
 */
int		ft_isalpha(int c);

/**
 * @brief [library] ctype.h •
 * Check whether 'c' is a valid ASCII digit character (i.e., 30 ('0') to 39
 * ('9')).
 * 
 * @param c Character as an integer.
 * @return Return 2048 if the character 'c' is an digit character, and a 0 if
 * not.
 */
int		ft_isdigit(int c);

/**
 * @brief [library] ctype.h •
 * Check whether 'c' is a valid ASCII alphanumeric character (i.e., isalpha(c)
 * || isdigit(c)).
 * 
 * @param c Character as an integer.
 * @return Return 8 if the character 'c' is an alphanumeric character, and 0 if
 * not.
 */
int		ft_isalnum(int c);

/**
 * @brief [library] ctype.h •
 * Checks whether 'c' is a valid ASCII character (i.e., 0 to 127).
 * 
 * @param c Character as an integer.
 * @return Return 1 if the character 'c' is an ASCII character, and a 0 if not.
 */
int		ft_isascii(int c);

/**
 * @brief [library] ctype.h •
 * Checks whether 'c'is a printable character including space (i.e., 32 (' ' or
 * space) to 126 ('~') in ASCII Table).
 * 
 * @param c Character as an integer.
 * @return Return 16384 if the character 'c' is an ASCII printable character,
 * and a 0 if not.
 */
int		ft_isprint(int c);

/**
 * @brief [library] string.h •
 * Calculates the length of the string pointed to by 's', excluding the
 * terminating null byte ('\0').
 * 
 * @param s String to be traversed.
 * @return Number of bytes in the string pointed to by 's'.
 */
size_t	ft_strlen(const char *s);

/**
 * @brief [libray] string.h •
 * Fills the first 'n' bytes of the memory area ponted to by 's' with the
 * constant byte 'c'.
 * 
 * @param s Memmory to be replaced.
 * @param c Constant byte used to replace.
 * @param n Number of bytes to be replaced.
 * @return Pointer to the replaced memory area.
 */
void	*ft_memset(void *s, int c, size_t n);

/**
 * @brief [libray] string.h •
 * Erases the data in the 'n' bytes of the memory starting at the location
 * pointed to by 's', by writing zeros ('\0' or 0) to that area.
 * 
 * @param s Memmory to be erased.
 * @param n Number of bytes to be erased.
 */
void	ft_bzero(void *s, size_t n);

/**
 * @brief [libray] string.h •
 * Copies 'n' bytes from memory area 'src' to memory area 'dest'. The memory
 * areas must not overlap.
 * 
 * @param dest Memory area to be replaced.
 * @param src Memory area to be copied.
 * @param n Number of bytes to be copied.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief [libray] string.h •
 * Copies 'n' bytes from memory area 'src' to memory area 'dest'. The memory
 * areas may overlap: Copying takes place as though the bytes in 'src' are first
 * copied into a temporary array that does not overlap 'src' or 'dest', and the
 * bytes are then copied from the temporary array to 'dest'.
 * 
 * @param dest Memory area to be replaced.
 * @param src Memory area to be moved.
 * @param n Number of bytes to be moved.
 */
void	*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief [libray] string.h •
 * Copy strings and is designed to be safer, more consistent, and less error
 * prone replacement for strncpy(). Unlike strncpy(), strlcpy() take the full
 * size of the buffer (not just the length) and guarantee to NUL-terminate the
 * result (as long as size is larger than 0). Note that a byte for the NUL
 * should be included in 'size'. Also note that strlcpy() only operate on true
 * “C” strings. This means that 'src' must be NUL-terminated.
 * 
 * @param dest Pointer to the destination string.
 * @param src Pointer to the source string.
 * @param size Size of the buffer.
 * @return Total length of the created string.
 */
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

/**
 * @brief [libray] string.h •
 * Concatenate strings and is designed to be safer, more consistent, and less
 * error prone replacement for strncat(). Unlike strncat(), strlcat() take the
 * full size of the buffer (not just the length) and guarantee to NUL-terminate
 * the result (as long as there is at least one byte free in 'dest'). Note that
 * a byte for the NUL should be included in 'size'. Also note that strlcat()
 * only operate on true “C” strings. This means that both src and dest must be
 * NUL-terminated.
 * 
 * @param dest Pointer to the destination string.
 * @param src Pointer to the source string.
 * @param size Size of the buffer.
 * @return Total length of the created string.
 */
size_t	ft_strlcat(char *dest, const char *src, size_t size);

/**
 * @brief [libray] ctype.h •
 * Convert lowercase letters to uppercase.
 * 
 * @param c Char to be converted.
 * @return Converted letter or 'c' if the conversion is not possible.
 */
int		ft_toupper(int c);

/**
 * @brief [libray] ctype.h •
 * Convert uppercase letters to lowercase.
 * 
 * @param c Char to be converted.
 * @return Converted letter or 'c' if the conversion is not possible.
 */
int		ft_tolower(int c);

/**
 * @brief [library] string.h •
 * Returns a pointer to the first occurrence of the character 'c' in the string
 * 's'.
 * 
 * @param s String to be scanned.
 * @param c Character as integer to search.
 * @return Pointer to the matched character or NULL if the character is not
 * found. The terminating null byte is considered part of the string, so that
 * if 'c' is specified as '\0', these functions return a pointer to the
 * terminator.
 */
char	*ft_strchr(const char *s, int c);

/**
 * @brief [library] string.h •
 * Returns a pointer to the last occurrence of the character 'c' in the string
 * 's'.
 * 
 * @param s String to be scanned.
 * @param c Character as integer to search.
 * @return Pointer to the matched character or NULL if the character is not
 * found. The terminating null byte is considered part of the string, so that
 * if 'c' is specified as '\0', these functions return a pointer to the
 * terminator.
 */
char	*ft_strrchr(const char *s, int c);

/**
 * @brief [library] string.h •
 * Compares the first (at most) 'n' bytes of strings s1 and s2. The locale is
 * not taken into account.
 * 
 * @param s1 Pointer to the first string.
 * @param s2 Pointer to the second string.
 * @param n Buffer size in bytes to compare both strings.
 * @return An integer less than, equal to, or greater than zero if s1 (or the
 * first n bytes thereof) is found, respectively, to be less than, to match, or
 * be greater than s2.
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief [library] string.h •
 * Scans the initial 'n' bytes of the memory area pointed to by 's' for the
 * first instance of 'c'. Both 'c' and the bytes of the memory area pointed to
 * by 's' are interpreted as unsigned char.
 * 
 * @param s Pointer to memory area to be scanned.
 * @param c Char as integers sought in the area.
 * @param n Number of bytes to be scanned.
 * @return Pointer to the matching byte or NULL if the character does not occur
 * in the given memory area.
 */
void	*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief [library] string.h •
 * Compares the first 'n' bytes (each interpreted as unsigned char) of the
 * memory areas 's1' and 's2'.
 * 
 * @param s1 First memory area where 'n' bytes will be compared.
 * @param s2 Second memory area where 'n' bytes will be compared.
 * @param n Number of Bytes to be compared.
 * @return Integer less than, equal to, or greater than zero if the first 'n'
 * bytes of 's1' is found, respectively, to be less than, to match, or be
 * greater than the first 'n' bytes of 's2'. For a nonzero return value, the
 * sign is determined by the sign of the difference between the first pair of
 * bytes (interpreted as unsigned char) that differ in 's1' and 's2'. If 'n' is
 * zero, the return value is zero.
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief [library] string.h •
 * Locates the first occurrence of the null-terminated string 'little' in the
 * string 'big', where not more than 'len' characters are searched. Characters
 * that appear after a '\0' character are not searched. Since the strnstr()
 * function is a FreeBSD specific API, it should only be used when portability
 * is not a concern.
 * 
 * @param big String to be searched by `little`.
 * @param little String to search in `big`.
 * @param len Number of bytes to search.
 * @return If 'little' is an empty string, 'big' is returned, if 'little' occurs
 * nowhere in 'big', NULL is returned, otherwise a pointer to the first
 * character of the first occurrence of 'little' is returned.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len);

/**
 * @brief [library] stdlib.h •
 * Converts the initial portion of the string pointed to by 'nptr' to int.
 * 
 * @param nptr Pointer to the string that must be converted.
 * @return The converted value.
 */
int		ft_atoi(const char *nptr);

/**
 * @brief [library] stdlib.h • [External Functions] malloc •
 * Allocates memory for an array of 'nmemb' elements of 'size' bytes each and
 * returns a pointer to the allocated memory. The memory is set to zero. If
 * 'nmemb' or 'size' is 0, then calloc() returns either NULL, or a unique
 * pointer value that can later be successfully passed to free(). If the
 * multiplication of 'nmemb' and 'size' would result in integer overflow, then
 * calloc() returns an error. By contrast, an integer overflow would not be
 * detected in the following call to malloc(), with the result that an
 * incorrectly sized block of memory would be allocated: malloc(nmemb * size);
 * 
 * @param nmemb Number of elements to be allocated.
 * @param size ize Size in bytes of each element.
 * @return Ponter to the allocated memory or NULL if 'nmemb' or 'size' is 0.
 */
void	*ft_calloc(size_t nmemb, size_t size);

/**
 * @brief  [libray] string.h • [External Functions] malloc •
 * Returns a pointer to a new string which is a duplicate of the string 's'.
 * Memory for the new string is obtained with malloc(), and can be freed with
 * free().
 * 
 * @param s String to be duplicated.
 * @return Pointer to the duplicated string, or NULL if insufficient memory was
 * available.
 */
char	*ft_strdup(const char *s);

/**
 * @brief [External Functions] malloc •
 * Allocates (with malloc()) and returns a substring from the string 's'. The
 * substring begins at index 'start' and is of maximum size 'len'.
 * 
 * @param s The string from which to create the substring.
 * @param start The start index of the substring in the string 's'.
 * @param len The maximum length of the substring.
 * @return The substring. NULL if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief [External Functions] malloc •
 * Allocates (with malloc()) and returns a new string, which is the result of
 * the concatenation of 's1' and 's2'.
 * 
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return The new string. NULL if the allocation fails.
 */
char	*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief [External Functions] malloc •
 * Allocates (with malloc()) and returns a copy of 's1' with the characters
 * specified in 'set' removed from the beginning and the end of the string.
 * 
 * @param s1 The string to be trimmed.
 * @param set The reference set of characters to trim.
 * @return The trimmed string. NULL if the allocation fails.
 */
char	*ft_strtrim(char const *s1, char const *set);

/**
 * @brief [External Functions] malloc, free •
 * Allocates (with malloc()) and returns an array of strings obtained by
 * splitting 's' using the character 'c' as a delimiter. The array must end with
 * a NULL pointer.
 * 
 * @param s The string to be split.
 * @param c The delimiter character.
 * @return The array of new strings resulting from the split. NULL if the
 * allocation fails.
 */
char	**ft_split(char const *s, char c);

/**
 * @brief [External Functions] malloc •
 * Allocates (with malloc()) and returns a string representing the integer
 * received as an argument. Negative numbers must be handled.
 * 
 * @param n The integer to convert.
 * @return The string representing the integer. NULL if the allocation fails.
 */
char	*ft_itoa(int n);

/**
 * @brief [External Functions] malloc •
 * Applies the function 'f' to each character of the string 's', and passing its
 * index as first argument to create a new string (with malloc()) resulting
 * from successive applications of 'f'.
 * 
 * @param s The string on which to iterate.
 * @param f The function to apply to each character.
 * @return The string created from the successive applications of 'f' or NULL if
 * the allocation fails.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Applies the function 'f' on each character of the string passed as
 * argument, passing its index as first argument. Each character is passed by
 * address to 'f' to be modified if necessary.
 * 
 * @param s The string on which to iterate.
 * @param f The function to apply to each character.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/**
 * @brief [External Functions] write •
 * Outputs the character 'c' to the given file descriptor.
 * 
 * @param c The character to output.
 * @param fd The file descriptor on which to write.
 */
void	ft_putchar_fd(char c, int fd);

/**
 * @brief [External Functions] write •
 * Outputs the string 's' to the given file descriptor.
 * 
 * @param s The string to output.
 * @param fd The file descriptor on which to write.
 */
void	ft_putstr_fd(char *s, int fd);

/**
 * @brief [External Functions] write •
 * Outputs the string 's' to the given file descriptor followed by a newline.
 * 
 * @param s The string to output.
 * @param fd The file descriptor on which to write.
 */
void	ft_putendl_fd(char *s, int fd);

/**
 * @brief [External Functions] write •
 * Outputs the integer 'n' to the given file descriptor.
 * 
 * @param n The integer to output.
 * @param fd The file descriptor on which to write.
 */
void	ft_putnbr_fd(int n, int fd);

/**
 * @brief [External Functions] malloc •
 * Allocates (with malloc()) and returns a new node. The member variable
 * 'content' is initialized with the value of the parameter 'content'. The
 * variable 'next' is initialized to NULL.
 * 
 * @param content The content to create the node with.
 * @return The new node.
 */
t_list	*ft_lstnew(void *content);

/**
 * @brief Adds the node 'new' at the beginning of the list.
 * 
 * @param lst The address of a pointer to the first link of a list.
 * @param new The address of a pointer to the node to be added to the list.
 */
void	ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Counts the number of nodes in a list.
 * 
 * @param lst The beginning of the list.
 * @return The length of the list.
 */
int		ft_lstsize(t_list *lst);

/**
 * @brief Returns the last node of the list.
 * 
 * @param lst The beginning of the list.
 * @return Last node of the list.
 */
t_list	*ft_lstlast(t_list *lst);

/**
 * @brief Adds the node 'new' at the end of the list.
 * 
 * @param lst The address of a pointer to the first link of a list.
 * @param new The address of a pointer to the node to be added to the list.
 */
void	ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief [External Functions] free •
 * Takes as a parameter a node and frees the memory of the node's content using
 * the function 'del' given as a parameter and free the node. The memory of
 * 'next' must not be freed.
 * 
 * @param lst The node to free.
 * @param del The address of the function used to delete the content.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @brief [External Functions] free •
 * Deletes and frees the given node and every successor of that node, using the
 * function 'del' and free(). Finally, the pointer to the list must be set to
 * NULL.
 * 
 * @param lst The address of a pointer to a node.
 * @param del The address of the function used to delete the content of the node
 * .
 */
void	ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief Iterates the list 'lst' and applies the function 'f' on the content of
 * each node.
 * 
 * @param lst The address of a pointer to a node.
 * @param f The address of the function used to iterate on the list.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief [External Functions] malloc, free •
 * Iterates the list 'lst' and applies the function 'f' on the content of each
 * node. Creates a new list resulting of the successive applications of the
 * function 'f'. The 'del' function is used to delete the content of a node if
 * needed.
 * 
 * @param lst The address of a pointer to a node.
 * @param f The address of the function used to iterate on the list.
 * @param del The address of the function used to delete the content of a node
 * if needed.
 * @return The new list. NULL if the allocation fails.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/**
 * @brief [External Functions] read, malloc, free •
 * Fills the first 'n' bytes of the memory area ponted to by 's' with the
 * constant byte 'c'.
 * 
 * @param fd The file descriptor to read from
 * @return Line read if it behaves correctly or NULL if there is nothing else to
 * read, or an error occurred.
 */
char	*get_next_line(int fd);

/**
 * @brief [library] string.h •
 * [External Functions] malloc, free, write, va_start, va_arg, va_copy, va_end •
 * Write output to stdout, the standard output stream under the control of a
 * format string that specifies how subsequent arguments (or arguments accessed
 * via the variable-length argument facilities of stdarg()) are converted for
 * output.
 * Conversions:
 * • '%c' char: Prints a single character;
 * • '%s' char *: Prints a string (as defined by the common C convention);
 * • '%p' unsigned long: The void * pointer argument has to be printed in
 * hexadecimal format;
 * • '%d' int: Prints a decimal (base 10) number;
 * • '%i' int: Prints an integer in base 10;
 * • '%u' unsigned int: Prints an unsigned decimal (base 10) number;
 * • '%x' unsigned int: Prints a number in hexadecimal (base 16) lowercase
 * format;
 * • '%X' unsigned int: Prints a number in hexadecimal (base 16) uppercase
 * format;
 * • '%%' Prints a percent sign;
 * 
 * @param s Plain text that may contain specifiers.
 * @param ... Undefined number of parameters, its each type will be defined by
 * the specifiers indicated in 's'.
 * @return Upon successful, return the number of characters printed (excluding
 * the null byte used to end output to strings). If an output error is
 * encountered, a negative value is returned.
 */
int		ft_printf(const char *s, ...);

#endif
