#include <stdio.h>
#include <windows.h>

int main()
{
  // ���������� ����������� dll
  HINSTANCE h;

  // ���������� ��������� �� �������, ���������� �� DLL
  // �������� �������� � ����� ����������� ������� �
  // �������, ���������� �� DLL, ����� � �� ���������,
  // �.�. �� ����� ���������� ������� ��������
  // GetProcAddress
  void (*DllFunc) (char *str);

  // ��������� MyFirstDLL
  h=LoadLibrary(L"Geometr.dll");

  // �������� ������ � ���� �������� ������ �������,
  // ������� ������ ���-�� �������� �� ����
  if (!h)
  {
    printf("������ - �� ���� ����� Geometr.dll\n");
    return 1;
  }

  // ������� GetProcAddress �������� ����� ������� Demo
  // � ����������� ��� ��������� DllFunc � ����� 
  // ����������� �����. ��� ���������� �.�.
  // GetProcAddress ���������� ���������� far-���������
  DllFunc=(void (*) (char *str))
            GetProcAddress(h,"Demo");

  // �������� ������ � ���� ����� ������� GetProcAddress
  // ���������� �������, ��� ������ ��������� ���������
  if (!DllFunc)
  {
    printf("������! � MyFirstDLL "
           "����������� �-���   Demo\n");
    return 1;
  }

  // ����� ������� Demo �� DLL
  DllFunc("Test");

  // �������� ������������ ���������� �� ������
  FreeLibrary(h);
  return 0;
}