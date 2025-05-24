/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Header file for unit. Every object which have status should inherit this class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Attackable.h"
#include "Interfaces/Damageable.h"
#include "Interfaces/UnitInterface.h"
#include "AITypes.h"

#include "Unit.generated.h"
class UHitPointsUI;
class UObjectPoolComponent;
class UWidgetComponent;
class UCharacterStatComponent;
class UCrowdControlComponent;
class UDamageUI;
class UDelegateBridgeSubsystem;
enum class EUnitEvent : uint8;
struct FBuffData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnitEvent);

UCLASS(Abstract)
class PROJECT_IK_API AUnit : public ACharacter, public IAttackable, public IDamageable, public IUnitInterface
{
	GENERATED_BODY()
	friend UDelegateBridgeSubsystem;
public:
	// Sets default values for this character's properties
	AUnit();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void Die() override;
	
	FVector GetForwardDir() const;
	void SetForwardDir(const FVector& Forward_Dir);

	void SetCurHidingCover(AActor* cover);
	AActor* GetCurHidingCover() const;

	virtual void Attack(AActor* target) override;

	UFUNCTION(BlueprintCallable)
	ECharacterType GetCharacterType() const;
	UCharacterStatComponent* GetCharacterStat();

	EUnitBoneType GetBoneType() const;

	
	UFUNCTION(BlueprintCallable)
	virtual void GetDamage(FDamageData data) override;
	
	UFUNCTION(BlueprintCallable)
	void Heal(float heal);

	UFUNCTION(BlueprintCallable)
	void ApplyBuff(FBuffData buff);

	UFUNCTION(BlueprintCallable)
	bool RemoveBuff(FName BuffName);

	UFUNCTION(BlueprintCallable)
	void ApplyCrowdControl(ECCType cc_type, float duration);

	void AcquireShield(float ShieldAmount, float Duration);
	
	UFUNCTION()
	virtual void GetStunned(float stun_duration) override;

	UFUNCTION()
	virtual void OnStunned() override;

	UFUNCTION()
	virtual void FinishStun() override;

	UFUNCTION()
	virtual void OnEnterBattleOnce();
	
	float GetPitchDiffBetweenTarget();

	float GetStunRequestID() const;

	UFUNCTION()
	void DispatchUnitEvent(EUnitEvent type);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UHitPointsUI> hp_UI_class_;
	
protected:
	void SetDamageUI(FDamageData data, bool is_evaded);
	FTransform GetActorTransformForDamageUI() const noexcept;

	void GetDamageByDot(FDamageData data);
	void GetDamageByPEM(FDamageData data);
	void GetDamageByMagic(FDamageData data);
	void RecoverAttackerByLifeSteal(FDamageData data);

protected:
	//Name/Character Type/Bone Type은 BP에서 초기화 되는것을 기대한다.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	FName character_name_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	ECharacterType character_type_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	EUnitBoneType bone_type_;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterStatComponent> character_stat_component_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Unit")
	TObjectPtr<UCrowdControlComponent> cc_component_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> stun_montage_;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Unit", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> hp_UI_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> stunned_montage_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageUI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UObjectPoolComponent> object_pool_component_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true"))
	EAIFindTargetType ai_find_target_type_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit", meta = (AllowPrivateAccess = "true"))
	FVector forward_dir_;
	
	UPROPERTY(Transient)
	FTimerHandle stun_timer_;

	UPROPERTY(Transient)
	TWeakObjectPtr<AActor> cur_hiding_cover_ = nullptr;

	UPROPERTY()
	TMap<EUnitEvent, FOnUnitEvent> on_unit_event_;

	UPROPERTY()
	FAIRequestID stun_ai_request_id_ = 2;

	bool is_first_attack_ = true;
	
	float capsule_half_height_ = 0.f;
	float capsule_radius_ = 0.f;
};