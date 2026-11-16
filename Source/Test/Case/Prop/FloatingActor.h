// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS()
class TEST_API AFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingActor();

	//创建一个静态网格体组件的变量，并且可以在细节面板中查看.
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

	//第二种制作方法
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh");
	UStaticMesh* NewMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FloatingActor");
	float FloatSpeed = 20.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FloatingActor");
	float RotationSpeed = 20.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
