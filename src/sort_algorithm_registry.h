#pragma once

#include <functional>
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "sort.h"

class SortAlgorithmRegistry {
public:
	using FactoryFunction = std::function<std::unique_ptr<Sort>()>;

	// singleton
	static SortAlgorithmRegistry& instance()
	{
		static SortAlgorithmRegistry reg;
		return reg;
	}

	void registerSortAlgorithm(const std::string& name, FactoryFunction factory) 
	{
		m_factories[name] = factory;
	}

	std::vector<std::string> getRegisteredNames() const
	{
		std::vector<std::string> names;
		names.reserve(m_factories.size());
		for (const auto& kv : m_factories) 
		{
			names.push_back(kv.first);
		}

		return names;
	}

	std::unique_ptr<Sort> createSortAlgorithm(const std::string& name) const
	{
		auto it = m_factories.find(name);
		if (it != m_factories.end()) 
		{
			return it->second();
		}

		throw std::runtime_error("Sorting algorithm not found: " + name);
	}


private:
	// enforce singleton usage
	SortAlgorithmRegistry() = default;

	std::map<std::string, FactoryFunction> m_factories;
};

// DERIVED_CLASS: name of the algorithm (e.g. BubbleSort<int>)
// NAME_STRING: human readable name
#define REGISTER_SORT_ALGORITHM(DERIVED_CLASS, NAME_STRING)                     \
  inline bool register_##DERIVED_CLASS() {                            \
    SortAlgorithmRegistry::instance().registerSortAlgorithm(                     \
      NAME_STRING,                                                    \
      [](){ return std::make_unique<DERIVED_CLASS>(); }               \
    );                                                                \
    return true;                                                      \
  }                                                                   \
  inline bool s_registered_##DERIVED_CLASS = register_##DERIVED_CLASS();