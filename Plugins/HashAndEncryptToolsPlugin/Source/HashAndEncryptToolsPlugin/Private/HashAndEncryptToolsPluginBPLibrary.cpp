// By Jason Hoku Levien, Published 2022


#include "HashAndEncryptToolsPluginBPLibrary.h"
#include "HashAndEncryptToolsPlugin.h"


#include "Serialization/BufferArchive.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/SecureHash.h"
#include "Internationalization/TextKey.h"


UHashAndEncryptToolsPluginBPLibrary::UHashAndEncryptToolsPluginBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), " HAET Created");

}






FString UHashAndEncryptToolsPluginBPLibrary::ConvertBytesToString(TArray <uint8> In)
{
	FString contents;
	FFileHelper::BufferToString(contents, In.GetData(), In.Num());

	FString BuiltString;

	for (int i = 0; i < In.Num(); i++) {


		BuiltString = BuiltString + FString::FromInt((int32)In[i]);


	}


	return contents;

}







FString UHashAndEncryptToolsPluginBPLibrary::CustomEncryptString(FString InString)
{
	FString alphanum = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ//=-_//\\,+:;<=>?!\'()*+,-.[]!@#$%^&*";
	FString outChars = "";

	if (InString.Len() < 2) {
		return  " ";
	}

	while (InString.Len() > alphanum.Len()) {
		alphanum += alphanum;
	}

	for (int i = 0; i < InString.Len(); ++i) {


		FString gotLetter = FString(InString.Mid(i, 1));

		int32 gotIndex = alphanum.Find(gotLetter);
		outChars += " " + FString::FromInt(gotIndex) + "";

	}


	return outChars;
}

FString UHashAndEncryptToolsPluginBPLibrary::CustomDecryptString(FString InString)
{
	FString alphanum = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ//=-_//\\,+:;<=>?!\'()*+,-.[]!@#$%^&*";
	FString outString = "";

	TArray<FString> parts;
	InString.ParseIntoArray(parts, TEXT(" "), true);

	for (const FString& part : parts)
	{
		if (part.IsNumeric())
		{
			int32 index = FCString::Atoi(*part);
			if (index >= 0 && index < alphanum.Len())
			{
				outString += alphanum.Mid(index, 1);
			}
		}
	}

	return outString;
}


FString UHashAndEncryptToolsPluginBPLibrary::ConvertStringToHash(FString InString)
{


	FString &gotString = InString;
	 
	const TCHAR gotTCHAR = FString(gotString).GetCharArray()[0];

	UE_LOG(LogTemp, Warning, TEXT("%s"), "ConvertStringToHash!"); 

	UE_LOG(LogTemp, Warning, TEXT("%s"), *gotString);


	FString outChars = FMD5::HashAnsiString(&gotTCHAR);  

	return FString("gotString");
}

FString UHashAndEncryptToolsPluginBPLibrary::GenerateRandomString(int Length)
{
	FString alphanum = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ//=-_//\\,+:;<=>?!\'()*+,-.[]!@#$%^&*";

	FString generatedString = "";

	for (int i = 0; i < Length; ++i) {

		generatedString = generatedString + alphanum[1 + (rand() % (alphanum.Len() - 2))];


	}


	return generatedString;
}

TArray<uint8> UHashAndEncryptToolsPluginBPLibrary::ConvertStringToBytes(FString InString)
{

	uint32 size = InString.Len();
	TArray<uint8> data;
	data.AddUninitialized(size);
	StringToBytes(InString, data.GetData(), size);
	return data;

}

FString UHashAndEncryptToolsPluginBPLibrary::SaveArrayOfBytesToFile(TArray <uint8> In, FString SavePath) {
	FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()) + TEXT("/GameData/credKey.txt");

	FFileHelper::SaveArrayToFile(In, *FilePath);
	return "True!";

}

TArray <uint8> UHashAndEncryptToolsPluginBPLibrary::LoadArrayOfBytesFromFile(FString FileName, FString SavePath) {
	FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()) + TEXT("/GameData/credKey.txt");

	TArray <uint8> gotData;
	FFileHelper::LoadFileToArray(gotData, *FilePath);
	return gotData;


}