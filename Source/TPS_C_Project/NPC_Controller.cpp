// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_Controller.h"

void ANPC_Controller::PlayTree()
{
	if (UseBlackboard(BB, Blackboard))
	{
		if (RunBehaviorTree(DialogTree))
		{
			//TODO
		}
	}
	
}

void ANPC_Controller::EndDialog()
{
	GetBrainComponent()->StopLogic(TEXT(""));
}
