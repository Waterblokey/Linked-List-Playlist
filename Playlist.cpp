#include <iostream>
#include <string>
#include <sstream>

#include "Playlist.h"

using namespace std;

Playlist::Playlist() {
	_head = new Node(Song_Entry(-1, "HEAD"));
	_prev_to_current = _head;
	_tail = _head;
	_size = 0;
}



Playlist::~Playlist() {
	delete _head;
	_size = 0;
}



Playlist::Song_Entry& Playlist::get_current_song() const {
	if (_prev_to_current == _tail) {
		return this->_head->get_song();
	}
	return _prev_to_current->get_next()->get_song();
}



// The following return "this" on success, null on failure. See the spec
// for why.
Playlist* Playlist::clear() {
//	Node* headNext;

	while (_size > 0) {
		if (_head->get_next() == nullptr) {
			break;
		}
		/*headNext = _head->get_next()->get_next();
		delete _head->get_next();
		_head->get_next() = headNext;*/
		_head->remove_next();
		_size--;
	}
	_tail = _head;
	_prev_to_current = _head;
	_head->insert_next(nullptr);

	return this;
}



Playlist* Playlist::rewind() {
	_prev_to_current = _head;
	return this;
}



Playlist* Playlist::push_back(const Song_Entry& s) {
	Node* prevSave = _prev_to_current;

	_prev_to_current = _tail; 
	insert_at_cursor(s);
	_prev_to_current = prevSave;

	return this;
}



Playlist* Playlist::push_front(const Song_Entry& s) {
	Node* prevSave = _prev_to_current;

	_prev_to_current = _head;
	insert_at_cursor(s);
	_prev_to_current = prevSave;
	return this;
}



Playlist* Playlist::insert_at_cursor(const Song_Entry& s) {
	Node* tempNode = new Node(s);

	tempNode->insert_next(_prev_to_current->get_next());
	_prev_to_current->insert_next(tempNode);

	if (tempNode->get_next() == nullptr) {
		_tail = _prev_to_current->get_next();
	}

	_size++;
	return this;
}



Playlist* Playlist::remove_at_cursor() {
	if (_prev_to_current == _tail) {
		return NULL;
	}
	/*Node* tempPoint = _prev_to_current->get_next()->get_next();
	delete _prev_to_current->get_next();
	_prev_to_current->insert_next(tempPoint);*/
	_prev_to_current->remove_next();

	_size--;

	return this;
}



Playlist* Playlist::advance_cursor() {
	if (_prev_to_current->get_next() == NULL) {
		return nullptr;
	}
	_prev_to_current = _prev_to_current->get_next();

	return this;
}



Playlist* Playlist::circular_advance_cursor() {
	if (_prev_to_current->get_next() == NULL) {
		return nullptr;
	}
	if (_prev_to_current->get_next() == _tail) {
		_prev_to_current = _head;
	}
	else {
		_prev_to_current = _prev_to_current->get_next();
	}
	

	return this;
}



// The following return the target payload (or sentinel) reference on success
Playlist::Song_Entry& Playlist::find_by_id(int id) const {
	Node* finder = _head;
	for (size_t i = 0; i <= _size; i++) {
		if (finder->get_song().get_id() == id) {
			return finder->get_song();
		}
		finder->insert_next(finder->get_next());
	}
//	_head->data = "_SENTINEL_";
	return this->_head->get_song();


	return _head->get_song();
}
Playlist::Song_Entry& Playlist::find_by_name(string songName) const {
	return _head->get_song();
}

string Playlist::to_string() const {
	return "";
}












bool Playlist::Song_Entry::set_id(int id) {
	if (id < 0) {
		return false;
	}

	_id = id;
	return true;
}

bool Playlist::Song_Entry::set_name(string name) {
	if (name == "") {
		return false;
	}

	_name = name;
	return true;
}






Playlist::Node::~Node() {
	
}

Playlist::Node* Playlist::Node::insert_next(Node* p) {
	_next = p;
	return p;
}
Playlist::Node* Playlist::Node::remove_next() {
	delete _next;
	_next = _next->_next;
	return this;
}


