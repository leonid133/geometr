#include <stdio.h>
#include <windows.h>

int main()
{
  // Дескриптор загружаемой dll
  HINSTANCE h;

  // Объявление указателя на функцию, вызываемой из DLL
  // Обратите внимание – имена объявляемой функции и
  // функции, вызываемой из DLL, могут и не совпадать,
  // т.к. за выбор вызываемой функции отвечает
  // GetProcAddress
  void (*DllFunc) (char *str);

  // Загружаем MyFirstDLL
  h=LoadLibrary(L"Geometr.dll");

  // Контроль ошибок – если загрузка прошла успешно,
  // функция вернет что-то отличное от нуля
  if (!h)
  {
    printf("Ошибка - не могу найти Geometr.dll\n");
    return 1;
  }

  // Вызовом GetProcAddress получаем адрес функции Demo
  // и присваиваем его указателю DllFunc с явным 
  // приведением типов. Это необходимо т.к.
  // GetProcAddress возвращает бестиповой far-указатель
  DllFunc=(void (*) (char *str))
            GetProcAddress(h,"Demo");

  // Контроль ошибок – если вызов функции GetProcAddress
  // завершился успешно, она вернет ненулевой указатель
  if (!DllFunc)
  {
    printf("Ошибка! В MyFirstDLL "
           "отсутствует ф-ция   Demo\n");
    return 1;
  }

  // Вызов функции Demo из DLL
  DllFunc("Test");

  // Выгрузка динамической библиотеки из памяти
  FreeLibrary(h);
  return 0;
}