/**
 * Copyright 2015 Vestel. All rights reserved.
 *
 * @brief This file defines an stub implementation for simple string operations. Each stub function
 * should be improved to satisfy the actual functionality declared in string_exercise.h
 */
#include "string_exercise.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

StringReturnType stringCreate(char** str, StringSizeType size)
{

	*str = (char*)malloc(size + 1);
	if(*str == NULL){
		return  string_return_allocation_error;
	}
	// string'i baslangicta bos olusturup sonradan deger verdikce dolmasi icin..
	(*str)[0] = '\0';
	
	return string_return_success;
    
}

void stringDestroy(char* str)
{
	if(str != NULL)
 	free(str);
}

StringSizeType stringLength(const char* str)
{
	StringSizeType length  = 0;
	while(str[length] != '\0'){
		length ++;
	}
    return length;
}

void stringCopy(char* destination, const char* source)
{
	int i  = 0;
	while(source[i] != '\0'){
		destination[i] = source[i];
		i++;
	}
	
	destination[i] = '\0';
}

StringReturnType stringDuplicate(char** duplicate, const char* str)
{
	StringSizeType length = strlen(str);
	
	*duplicate = (char*)malloc((length +1) * sizeof(char));
	if(*duplicate == NULL){
		return string_return_allocation_error;
	}
	
	strcpy(*duplicate,str);
	
	return string_return_success;
    
}


StringReturnType stringConcat(char** destination, const char* source)
{
	StringSizeType destLength = (*destination) ? strlen(*destination) : 0;
	StringSizeType srcLength = strlen(source);
	
	char* concatenated = (char*)malloc((destLength + srcLength + 1) * sizeof(char)) ;
	if(concatenated == NULL){
		return string_return_allocation_error;
	}
	
	if(*destination){
		strcpy(concatenated,*destination);
	}
	
	strcat(concatenated + destLength,source);
	
	*destination = concatenated;
	return string_return_success;
    
}

StringReturnType stringCopySafe(
        char* destination,
        StringSizeType destination_size,
        const char* source,
        StringSizeType source_length)
{
    size_t actual_source_length = strlen(source);
    if (source_length < actual_source_length) {
        actual_source_length = source_length;
    }

    // Hedef dizinin boyutunu kontrol etme:
    if (destination_size <= actual_source_length) {
        return string_return_destination_overflow;
    }

    // Güvenli bir şekilde içeriği kopyalayalım
    strncpy(destination, source, actual_source_length);
    destination[actual_source_length] = '\0'; // Hedef diziyi NULL-terminated yapalım

    return string_return_success;
}

StringReturnType stringFindSubstring(
        const char* string_to_search,
        const char* substring,
        const char** position)
{
    if (string_to_search == NULL || substring == NULL) {
        return string_return_not_found;
    }

    size_t string_length = strlen(string_to_search);
    size_t substring_length = strlen(substring);

    if (substring_length > string_length) {
        return string_return_not_found;
    }

    // Alt diziyi arayalım
    const char* found_position = strstr(string_to_search, substring);

    if (found_position == NULL) {
        return string_return_not_found;
    }

    // Alt dizi bulunduğu durumda, başlangıç konumunu position işaretçisine atayalım
    *position = found_position;

    return string_return_success;
}
/*
int main(){
	char* myString;
	StringSizeType size = 50;
	
	StringReturnType result = stringCreate(&myString,size);
	if(result == string_return_success){
		printf("Bellek tahsisi basarili. Bellek adresi: %p\n",(void*)myString);
		
	strcpy(myString,"Hello world");
	StringSizeType length = stringLength(myString);
	printf("C string'inin uzunlugu: %u\n",length);
	
	// kullandiktan snra bellegi serbest birakiyoruz..
	stringDestroy(myString);
	
	const char* sourceString = "Software engineer";
	char destinationString[50];
	
	
	stringCopy(destinationString,sourceString);
	
	printf("Source string: %s\n",sourceString);
	printf("Copied string: %s\n",destinationString);
	
	}
	else{
		printf("Bellek tahssi basarisiz.\n");
	}
	const char* sourceString2 = "Helllo world";
	char* duplicatedString;
	
	StringReturnType result2 = stringDuplicate(&duplicatedString,sourceString2);
	if(result2 == string_return_success){
		printf("Source string2: %s\n",sourceString2);
		printf("Duplicated string: %s\n",duplicatedString);
	}else{
		printf("Memory allocation error!\n");
	}
	
	char* destinationString = NULL;
	destinationString = (char*)malloc(20 * sizeof(char));
	strcpy(destinationString, "Yazilim, ");
	StringReturnType result3 = stringConcat(&destinationString,"Muhendisligi");
	
	if(result3 == string_return_success){
		printf("Concatenated string: %s\n",destinationString);
		stringDestroy(destinationString);
	}else{
		printf("Memory allocation error!");
	}
	return 0;
}
*/
