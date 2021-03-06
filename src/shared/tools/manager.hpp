#pragma once
#include "component.hpp"
#include <cassert>
#include <set>
#include <vector>

namespace tee3d::shared::mgr {
template <typename Element> struct manager;
template <typename Element> manager<Element> &get_manager();
template <> struct manager<component> {
	using element_type = component;
	std::vector<element_type *> registry;
	size_t push(element_type *data) {
		assert(data->id == -1);
		size_t pos = registry.size();
		data->id = pos;
		registry.push_back(data);
		return pos;
	}
	void pop(element_type *data) {
		registry[data->id] = nullptr;
		data->id = -1;
	}

	manager(const manager &) = delete;
	manager(manager &&) = delete;
	manager &operator=(const manager &) = delete;
	manager &operator=(manager &&) = delete;

private:
	manager() = default;
	friend manager<component> &get_manager<component>();
};
template <typename Element> manager<Element> &get_manager() {
	static manager<Element> buffer{};
	return buffer;
}
template <typename Element> struct manager {
	using element_type = Element;
	std::set<size_t> registry;
	size_t push(element_type *data) {
		size_t pos = get_manager<component>().push(data);
		registry.insert(pos);
		return pos;
	}
	void pop(element_type *data) {
		registry.erase(data->id);
		return get_manager<component>().pop(data);
	}

	manager(const manager &) = delete;
	manager(manager &&) = delete;
	manager &operator=(const manager &) = delete;
	manager &operator=(manager &&) = delete;

private:
	manager() = default;
	friend manager<Element> &get_manager<Element>();
};
}
