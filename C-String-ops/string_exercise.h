/**
 * Copyright 2015 Vestel. All rights reserved.
 *
 * @brief This file declares a programming API for simple string operations.
 */

#ifndef CABOT_STRING_EXERCISE_H_INCLUDED
#define CABOT_STRING_EXERCISE_H_INCLUDED

// typedef -> bir veri turune yeni bir isim vermek icin.
typedef enum
{
    string_return_success,
    string_return_allocation_error,
    string_return_source_overflow,
    string_return_destination_overflow,
    string_return_not_found

} StringReturnType;

// unsigned -> isaretsiz yani negatif olmayan sayilari tanimlar. bellek boyutu gibi pozitif degerlerin kullanilacagi ornkelerde kullanilir.
typedef unsigned int StringSizeType;
// malloc ve calloc -> bellekten alah tahsisi icin kullanilirlar. Farklari:
// malloc() -> baslangic degerleri belli olmayan bellek tahsis eder.
// calloc() -> baslangicta butun alani sifirlar.

/**
 * @brief Allocates a C string of given size, uses C style memory allocation (malloc()/calloc())
 * @param str Pointer to store allocated memory location
 * @param size Size of the memory location to allocate
 * @return string_return_success if memory is successfully allocated,
 *         string_return_allocation_error otherwise
 */
StringReturnType stringCreate(char** str, StringSizeType size);

/**
 * @brief Destroys a given C string, uses C style memory allocation (free())
 * @param str C string to destroy
 */
void stringDestroy(char* str);

/**
 * @brief Calculates length of a given C string
 * @param str C string to calculate length
 * @return Length of the given C string
 */
StringSizeType stringLength(const char* str);

/**
 * @brief Copies contents of one C string to an other C string, destination string should be
 *        allocated
 * @param destination C string buffer to copy to. Buffer should be pre-allocated.
 * @param source C string to copy from
 */
void stringCopy(char* destination, const char* source);

/**
 * @brief Creates duplicate of a given C String, uses C style allocation (malloc())
 * @param[out]duplicate Address of a pointer to store duplicated C string.
 * @param str C string to duplicate.
 * @return string_return_success if memory is successfully allocated,
 *         string_return_allocation_error otherwise
 */
StringReturnType stringDuplicate(char** duplicate, const char* str);

/**
 * @brief Concatenates one C string to the end of other one. Destination string is reallocated to
 *        match the total size of two strings. Address of destination string will be changed after a call
 *        to this function. Uses C style memory allocation/deallocation (malloc()/calloc()/free())
 * @param destination C string that will store the appended source string.
 * @param source Address of string to be appended to the destination string.
 * @return string_return_success if successfully concatenated strings
 *         string_return_allocation_error if can not allocate buffer to concatenate strings.
 */
StringReturnType stringConcat(char** destination, const char* source);

/**
 * @brief Copies contents of one C string to an other C string, destination string should be
 *        allocated.
 * @param destination C string buffer to copy to. Buffer should be pre-allocated.
 * @param destination_size Size of the destination buffer
 * @param source C string to copy from
 * @param source_length Length of the first string
 * @return string_return_success on success,
 *         string_return_destination_overflow if destination is not large enough
 */
StringReturnType stringCopySafe(
    char* destination,
    StringSizeType destination_size,
    const char* source,
    StringSizeType source_length);

/**
 * @brief Finds position of a C substring in a given C string
 * @param string_to_search C string to search
 * @param substring Substring to find
 * @param[out] position  Points to the beginning of substring in target
 * @return string_return_success if found, position points to the beginning of substring in target
 *         string_return_not_found if not found, position is undefined and should not be used.
 */
StringReturnType stringFindSubstring(
    const char* string_to_search,
    const char* substring,
    char const ** position);

#endif /* CABOT_STRING_EXERCISE_H_INCLUDED */
