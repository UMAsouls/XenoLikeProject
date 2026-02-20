// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtDataAsset.h"


FPrimaryAssetId UArtDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(FPrimaryAssetType("ArtData"), GetFName());
};