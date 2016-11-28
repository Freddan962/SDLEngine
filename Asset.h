#ifndef ASSET_H
#define ASSET_H

template <class T>
class Asset
{
public:
	void add(std::string name, T asset)
	{
		if (mAssets.find(name) != mAssets.end())
			return;

		mAssets.insert(std::pair<std::string, T>(name, asset));
	}

	T get(std::string name)
	{
		auto pos = mAssets.find(name);

		if (pos == mAssets.end())
			return nullptr;
		else
			return pos->second;
	}

private:
	std::map<std::string, T> mAssets;

};

#endif