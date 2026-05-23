#pragma once

template<typename T, int size>
void Safe_Del_Array(T* (&array)[size])
{
	for (int i = 0; i < size; ++i)
	{
		if (array[i] != nullptr)
		{
			delete array[i];
			array[i] = nullptr;
		}
	}
}

template<typename T>
void Safe_Del_Vector(std::vector<T*>& vector)
{
	for (int i = 0; i < vector.size(); ++i)
	{
		if (vector[i] != nullptr)
		{
			delete vector[i];
		}
	}

	vector.clear();
}

void DrawDebugRect(const Vector3& position, const Vector3& rotation, const Vector3& scale, float durtaion, const Vector4& color);
void DrawDebugRect(const Matrix& matWorld, float durtaion, const Vector4& color);
void DrawDebugCircle();
void DrawDebugLine();