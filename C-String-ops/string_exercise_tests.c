/** Copyright 2015 Vestel. All rights reserved.
 *
 * @brief This file defines a set of unit tests for testing the implementation of the API declared
 * in string_exercise.h. This file should be extended to cover all other functions declared in
 * string_exercise.h
 */

#include "string_exercise.h"
#include <stdio.h>

typedef enum
{
    true  = 1,
    false = 0
}Boolean;

const char passed_message[] = "PASS";
const char fail_message[] = "FAIL";

/**
 * @brief Macro to call a unit test and print its result
 */
#define TEST(x)                                                                         \
                do                                                                      \
                {                                                                       \
                    printf("%s(): %s\n", #x, x() ? passed_message : fail_message);      \
                }                                                                       \
                while(0)

Boolean test_string_create()
{
    const StringSizeType size = 10;
    char* str;

    StringReturnType result = stringCreate(&str, size);

    // Bellek tahsisi başarılı oldu mu?
    if (result == string_return_success)
    {
        // Bellek tahsis edildi mi?
        if (str != NULL)
        {
            // Dizinin ilk karakteri '\0' mı? (başlangıçta boş oluşturulmuş mu?)
            if (str[0] == '\0')
            {
                // Bellek tahsisi ve başlangıç değeri başarılı
                // Bellek tahsis edilen diziyi serbest bırakalım
                stringDestroy(str);
                return true;
            }
        }
    }

    // Bellek tahsisi veya başlangıç değeri başarısız oldu
    // Bellek tahsis edilen diziyi serbest bırakalım (çünkü test başarısız)
    stringDestroy(str);
    return false;
}

Boolean test_string_destroy()
{
     const StringSizeType size = 10;
    char* str = (char*)malloc((size + 1) * sizeof(char));

    // Bellekte diziyi başarılı bir şekilde oluşturduk mu?
    if (str != NULL)
    {
        // Bellekte oluşturulan diziyi serbest bırakıyoruz
        stringDestroy(str);
	str = NULL;
            return true;
    }

    // Bellek serbest bırakılamadı, test başarısız
    return false;
}

Boolean
test_string_length()
{
    const char str[] = "This is a sample string to used to test stringLength() function";
    // This calculates size of string[] including '\0' at end.
    const StringSizeType buffer_length = sizeof(str)/sizeof(char);
    // So we subtract 1.
    const StringSizeType test_length = buffer_length - 1;

    StringSizeType calculated_length = stringLength(str);

    if(test_length == calculated_length)
    {
        return true;
    }
    else
    {
        return false;
    }

}

Boolean test_string_copy()
{
    const char source[] = "HELLO WORLD";
    const int max_length = 100; // Maksimum hedef dizi boyutu
    char destination[max_length];

    // source dizisini destination dizisine kopyalayalım
    stringCopy(destination, source);

    // Kopyalama başarılı mı?
    // İlk olarak, kaynaktaki ve hedefteki metin aynı olmalı
    if (strcmp(destination, source) == 0)
    {
        // İkincil olarak, hedef dizinin sonlandırıcı karakterle bitip bitmediğini kontrol edelim
        // Yani hedef dizi, tamamen kaynak diziyi kopyaladıktan sonra sonlandırıcı karakterle bitiyor olmalı
        int source_length = strlen(source);
        if (destination[source_length] == '\0')
        {
            // Test başarılı, kopyalama doğru yapıldı
            printf("Source string: %s\n",source);
            printf("Copied string: %s\n",destination);
            return true;
        }
    }
    // Kopyalama başarısız oldu
    return false;
}

Boolean test_string_duplicate()
{
    const char str[] = "Kopyalanan metin.";
    char* duplicate;

    StringReturnType result = stringDuplicate(&duplicate, str);

    // Bellek tahsisi başarılı oldu mu?
    if (result == string_return_success)
    {
        // Duplicate dizisi oluşturuldu mu?
        if (duplicate != NULL)
        {
            // Duplicate dizisinin içeriği kaynak dizisiyle aynı mı?
            if (strcmp(duplicate, str) == 0)
            {
                // Test başarılı, kopyalama ve bellek tahsisi doğru yapıldı
                printf("Source: %s\n",str);
                printf("Duplicate: %s\n",duplicate);
                // Duplicate dizisini serbest bırakalım
                stringDestroy(duplicate);
                return true;
            }
        }
    }

    // Bellek tahsisi veya kopyalama başarısız oldu
    // Duplicate dizisini serbest bırakalım (test başarısız durumda)
    stringDestroy(duplicate);
    return false;
}

Boolean test_string_concat()
{
    const char str1[] = "This is the first string";
    const char str2[] = " and this is the second string";
    char* destination = NULL;

    // İlk olarak, destination dizisini oluşturup içeriğini boş olarak ayarlayalım
    StringReturnType result = stringCreate(&destination, 0);

    if (result == string_return_success)
    {
        // destination dizisine str1'i ekleyelim
        result = stringConcat(&destination, str1);

        // destination dizisine str1'i eklemek başarılı oldu mu?
        if (result == string_return_success)
        {
            // destination dizisini ve str1'i içeren birleştirilmiş dizi oluşturuldu mu?
            // Bu dizi şimdi str2'yi içerecek şekilde güncellenmiş olmalı
            result = stringConcat(&destination, str2);

            if (result == string_return_success)
            {
                // destination dizisi, str1 ve str2'yi birleştirerek başarılı bir şekilde güncellenmiş olmalı
                // Oluşturulan birleştirilmiş diziyi ekrana yazdıralım
                printf("Concatenated String: %s\n", destination);

                // Test başarılı, bellek yönetimi ve birleştirme işlemi doğru yapıldı
                // destination dizisini serbest bırakalım
                stringDestroy(destination);
                return true;
            }
        }
    }

    // Bellek tahsisi veya birleştirme işlemi başarısız oldu
    // destination dizisini serbest bırakalım (test başarısız durumda)
    stringDestroy(destination);
    return false;
}

Boolean test_string_copy_safe()
{
    const char source[] = "This is the source string";
    const StringSizeType destination_size = 26;
    char destination[destination_size];

    StringReturnType result = stringCopySafe(destination, destination_size, source, strlen(source));

    // Hedef dizinin boyutunu aşıp aşmadığını kontrol edelim
    if (result == string_return_destination_overflow)
    {
        // Hedef dizisi belirtilen boyuttan büyük oldu ve taşma hatası döndü
        return false;
    }

    // Hedef dizisi belirtilen boyut içinde kaldı
    // Şimdi, kaynak dizinin başarıyla hedef diziye kopyalanıp kopyalanmadığını kontrol edelim
    if (strcmp(destination, source) == 0)
    {
        // Kopyalama başarılı, kaynak dizisi hedef diziye doğru bir şekilde kopyalandı
        return true;
    }

    // Kopyalama başarısız oldu
    return false;
}

Boolean test_string_find_substring()
{
    const char str[] = "This is a sample string";
    const char sub[] = "sample";
    const char* position;

    // Alt diziyi arayalım
    StringReturnType result = stringFindSubstring(str, sub, &position);

    // Alt dizi bulundu mu?
    if (result == string_return_success)
    {
        // Alt dizi bulundu ve position işaretçisi güncellendi mi?
        if (position != NULL)
        {
            // position işaretçisi, alt dizinin başlangıç konumunu gösteriyor mu?
            if (position == strstr(str, sub))
            {
                // Test başarılı, alt dizi bulundu ve position işaretçisi doğru bir şekilde güncellendi
                return true;
            }
        }
    }

    // Alt dizi bulunamadı veya position işaretçisi güncellenmedi
    return false;
}

//TODO: Add other unit tests here.

int main()
{
    TEST(test_string_create);
    TEST(test_string_destroy);
    TEST(test_string_length);
    TEST(test_string_copy);
    TEST(test_string_duplicate);
    TEST(test_string_concat);
    TEST(test_string_copy_safe);
    TEST(test_string_find_substring);
    // TODO: Call other unit tests here

    return 0;
}
