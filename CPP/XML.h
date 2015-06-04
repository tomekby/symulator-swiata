#pragma once
#include "console.h"
#include <fstream>
#include <sstream>
#include <vector>

namespace XML {

	const console::string WHITESPACE = _(" \t\r\n");

	class Reader {
	public:
		typedef std::vector<std::pair<console::string, console::string>> attribs_t;
		typedef std::pair<Reader*, size_t> nodes_t;

		Reader(const console::string &file_name);
		Reader() = default;
		Reader get_node(const console::string &name);
		nodes_t get_nodes(const console::string &name);
		const console::string inner_text();
		const console::string outer_text() { return _content; };
		const console::string attrib(const console::string &name);
		template<class T> static void init_from_xml(T *o, const attribs_t &vals);
		template<class T> static void init_from_xml(T *o, const nodes_t &nodes);

		inline const bool is_empty() { return !_content.length(); }
	private:
		typedef std::pair<console::string, console::string> attr_type;

		Reader(const console::string &content, const bool node_init) { if (node_init) _content = content; }
		Reader& get_attribs();
		const console::string rtrim(const console::string &val);
		const console::string ltrim(const console::string &val);
		const console::string trim(const console::string &val);
		void clear_whitespace_after(const console::string &str);
		void erase_fragment(const size_t from, const size_t to);
		template<class buff_type>
		void resize_buffer(buff_type *&buff, size_t &size, const size_t count);

		console::string _last_node;
		console::string _content;
		attr_type *_attribs = nullptr;
		size_t _attribs_count = 1;
		console::string _inner_text;
		size_t _cur_pos = 0;
	};

	class Writer {
	public:
		Writer(const console::string &filename) : _filename(filename) {
			file = std::wofstream(_filename);
		}
		~Writer() { save(); }
		void save() {
			if (!saved) {
				file << _content;
				file.close();
				saved = true;
				_content = console::string();
			}
		}
		template<class T> console::string get_xml(const T &o) { return console::string(); };
	private:
		void add_xml(console::string &s) {
			_content += s;
			saved = false;
		}

		console::string _filename;
		console::string _content;
		std::wofstream file;
		bool saved = false;
	};
}