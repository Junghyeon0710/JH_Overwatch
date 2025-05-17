// Fill out your copyright notice in the Description page of Project Settings.


#include "LyraCameraModeCharacterSelect.h"


ULyraCameraModeCharacterSelect::ULyraCameraModeCharacterSelect()
{
	CameraDistance = 400.f;
}

void ULyraCameraModeCharacterSelect::UpdateView(float DeltaTime)
{
		
	AActor* TargetActor = GetTargetActor();
	if (!TargetActor)
	{
		return;
	}

	// ▶ 캐릭터 위치 (약간 위로)
	FVector TargetLocation = TargetActor->GetActorLocation() + FVector(0.f, 0.f, 80.f);

	// ▶ 카메라를 캐릭터 앞에 위치시킴 (ForwardVector의 반대 방향 → 정면에서 바라보기)
	FVector CameraOffset = -TargetActor->GetActorForwardVector() * CameraDistance;

	// ▶ 최종 카메라 위치 = 캐릭터 앞쪽 위치
	FVector CameraLocation = TargetLocation + CameraOffset;

	// ▶ 카메라가 캐릭터를 바라보도록 회전
	FRotator CameraRotation = (TargetLocation - CameraLocation).Rotation();

	// ▶ View 세팅
	View.Location = CameraLocation;
	View.Rotation = CameraRotation;
	View.ControlRotation = CameraRotation;
	View.FieldOfView = FieldOfView;
}