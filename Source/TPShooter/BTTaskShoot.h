// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskShoot.generated.h"

/**
 *
 */
UCLASS()
class TPSHOOTER_API UBTTaskShoot : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskShoot();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
