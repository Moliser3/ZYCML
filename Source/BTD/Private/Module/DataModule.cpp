// Fill out your copyright notice in the Description page of Project Settings.


#include "Module/DataModule.h"

DataModule::DataModule()
{
	//创建一个接口 提供"获取"和"修改"方法  创建一个基本的角色数据结构.
}

DataModule::~DataModule()
{
}

float DataModule::GetHealth() const { return Health; }
void DataModule::SetHealth(float Value) { Health = Value; }

float DataModule::GetEnergy() const { return Energy; }
void DataModule::SetEnergy(float Value) { Energy = Value; }

float DataModule::GetWalkSpeed() const { return WalkSpeed; }
void DataModule::SetWalkSpeed(float Value) { WalkSpeed = Value; }

float DataModule::GetRunSpeed() const { return RunSpeed; }
void DataModule::SetRunSpeed(float Value) { RunSpeed = Value; }

float DataModule::GetRotationSpeed() const { return RotationSpeed; }

void DataModule::SetRotationSpeed(float Value) { RotationSpeed = Value; }
