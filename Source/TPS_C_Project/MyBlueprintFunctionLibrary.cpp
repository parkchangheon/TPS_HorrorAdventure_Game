// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

int UMyBlueprintFunctionLibrary::EasyPlus(int a, int b)
{
	int c = a + b;

	UE_LOG(LogTemp, Log, TEXT("result = %d"), c);

	return c;
}


// constructorHelpers Ŭ������ �����ڿ��� Ŭ������ �ʱ�ȭ�ϴµ� ������ �ִ� Ŭ�����̴�.
// ������ �������� ���ҽ��� ��� ����Ʈ Ŭ������ �ҷ����� �۾��� �����ִ� ����� ������ �ִ�.
// ������ �̿��� �Լ������� ������ �߻��Ѵ�.


