/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.10.2024
Summary : Source file for Common functions.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/CommonFunctions.h"

#include "Environments/Cover.h"

ACover* CommonFunctions::FindBestCover(TArray<AActor*>& cover_candidates, FVector attack_target_pos, float fire_range)
{
	for(const auto& elem : cover_candidates)
	{
		if(ACover* casted_cover = Cast<ACover>(elem))
		{
			//만약 cover가 부서져있거나 이미 다른 주인이 있다면 넘어간다.
			if(casted_cover->IsBroken() || casted_cover->HasCoveringOwner()) continue;
					
			FVector cover_pos = elem->GetActorLocation();
			//만약 엄폐물에서의 위치와 가장 가까운 적의 거리가 사거리 보다 길다면 넘어간다.
			if(FVector::Dist2D(cover_pos, attack_target_pos) > fire_range) continue;

			FVector cover_to_target = attack_target_pos - cover_pos;
			cover_to_target.Normalize();
					
			float angle_similarity = FVector::DotProduct(cover_to_target, casted_cover->GetActorForwardVector());
			if(angle_similarity < 0.5) continue;
					
			return casted_cover;
		}
	}
	return nullptr;
}