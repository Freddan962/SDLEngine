#ifndef MAPVECTOR_H
#define MAPVECTOR_H

#include <map>
#include <vector>
#include <string>

template <class T>
class MapVector
{
public:
	void add(std::string name, T content)
	{
		if (mContent.find(name) != mContent.end())
		{
			mContent.at(name).push_back(content);
		}
		else
		{
			std::vector<T> contents;
			contents.push_back(content);
			mContent.insert(std::pair<std::string, std::vector<T>>(name, contents));
		}
	}

	std::vector<T> get()
	{
		std::vector<T> contents;

		for (auto pair : mContent)
		{
			std::vector<T> pairContent = pair.second;

			for (auto content : pairContent)
				contents.push_back(content);
		}

		return contents;
	}

	std::vector<T>* get(std::string name)
	{
		if (mContent.find(name) != mContent.end())
			return &mContent.at(name);

		return nullptr;
	}

private:
	std::map<std::string, std::vector<T>> mContent;
};

#endif