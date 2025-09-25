// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/KeyItem.h"
#include "Characters/Eve.h"

void AKeyItem::OnPickup(AEve* Player)
{
	if (Player)
	{
		Player->bHasKey = true;
		Destroy();
	
	}
}
