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
	Node *pHead = _head;
	Node *pNext;
	while (pHead != nullptr) {
		pNext = pHead->get_next();
		delete pHead;
//		cout << "deleted Playlist" << endl;
		pHead = pNext;
	}

	_head = NULL;
	_size = 0;
}



Playlist::Song_Entry& Playlist::get_current_song() const {
	if (_prev_to_current == _tail) {
		return this->_head->get_song();
	}
	return _prev_to_current->get_next()->get_song();
}



// The following return "this" on success, null on failure.
Playlist* Playlist::clear() {

	while (_size > 0) {
		if (_head->get_next() == nullptr) {
			break;
		}
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
		return nullptr;
	}

	if (_prev_to_current->remove_next() != nullptr) {
		_size--;
	}

	if (_prev_to_current->get_next() == nullptr) {
		_tail = _prev_to_current;
	}


	return this;
}



Playlist* Playlist::advance_cursor() {
	if (_prev_to_current->get_next() == nullptr) {
		return nullptr;
	}
	_prev_to_current = _prev_to_current->get_next();

	return this;
}



Playlist* Playlist::circular_advance_cursor() {
	if (_prev_to_current->get_next() == nullptr) {
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
	Node* finderNext;

	for (size_t i = 0; i <= _size; i++) {
		finderNext = finder->get_next();
		cout << finder->get_song().get_id() << endl;
		if (finder->get_song().get_id() == id) {
			return finder->get_song();
		}
		finder = finderNext;
	}

	return this->_head->get_song();
}

Playlist::Song_Entry& Playlist::find_by_name(string songName) const {
	Node* finder = _head;
	Node* finderNext;

	for (size_t i = 0; i <= _size; i++) {
		finderNext = finder->get_next();
		if (finder->get_song().get_name() == songName) {
			return finder->get_song();
		}
		finder = finderNext;
	}
	return this->_head->get_song();
}

string Playlist::to_string() const {
	std::string stringSum;
	std::string subString;
	std::stringstream stream;

	int count = 0;

	Node* finder = _head;
	Node* finderNext;

	stream << _size;
	subString = stream.str();

	stringSum = "Playlist: " + subString + " entries." + '\n';

	stream.str("");

	for (size_t i = 0; i <= _size; i++) {
		finderNext = finder->get_next();
		finder = finderNext;

		if (count > 24) {
			stringSum.append("...\n");
			break;
		}
		else if (finder == nullptr) {
			break;
		}

		stream << finder->get_song().get_id();
		subString = stream.str();

		stringSum.append("{ id: " + subString + ", name: " + finder->get_song().get_name() + " }");

		if (finder == _tail) {
			stringSum.append(" [T]\n");
		}
		else if (finder == _prev_to_current) {
			stringSum.append(" [P]\n");
		}
		else{
			stringSum.append("\n");
		}

		count++;
		stream.str("");
	}
	return stringSum;
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
//	cout << "Destructing" << endl;
	_next = nullptr;

}



Playlist::Node* Playlist::Node::insert_next(Node* p) {
	this->_next = p;
	return p;
}


Playlist::Node* Playlist::Node::remove_next() {
	if (this->_next == nullptr) {
		return nullptr;
	}

	Node* pNext = this->_next;
	this->_next = this->_next->_next;
	pNext->_next = nullptr;

	return this;
}


//int main() {
//	Playlist tunes;
//	Playlist::Song_Entry Gualala;
//	Playlist::Song_Entry Portland(5, "Mac");
//	Playlist::Song_Entry Vancouver(-1, "");
//
//	tunes.push_back(Gualala);
//	cout << "push_back Gualala: " << tunes.get_current_song() << endl;
//	cout << "size: " << tunes.get_size() << endl;
//	tunes.push_front(Portland);
//	cout << "push_front Portland: " << tunes.get_current_song() << endl;
//	cout << "size: " << tunes.get_size() << endl;
//	//tunes.remove_at_cursor();
//	//cout << "remove: " << tunes.get_current_song() << endl;
//	//cout << "size: " << tunes.get_size() << endl;
//
//	//tunes.remove_at_cursor();
//	//cout << "remove 2 electric boogaloo: " << tunes.get_current_song() << endl;
//	//cout << "size: " << tunes.get_size() << endl;
//
//	tunes.advance_cursor();
//	cout << "advance cursor: " << tunes.get_current_song() << endl;
//	cout << "size: " << tunes.get_size() << endl;
//
//	tunes.insert_at_cursor(Portland);
//	cout << "insert Portland: " << tunes.get_current_song() << endl;
//	cout << "size: " << tunes.get_size() << endl;
//
//	cout << tunes.find_by_id(5) << endl;
//
//	tunes.circular_advance_cursor();
//	cout << "circular advance cursor 1 : " << tunes.get_current_song() << endl;
//	cout << "size: " << tunes.get_size() << endl;
//
//	tunes.circular_advance_cursor();
//	cout << "circular advance cursor 2 : " << tunes.get_current_song() << endl;
//	cout << "size: " << tunes.get_size() << endl;
//
//	tunes.circular_advance_cursor();
//	cout << "circular advance cursor 3 : " << tunes.get_current_song() << endl;
//	cout << "size: " << tunes.get_size() << endl;
//
//	cout << tunes.to_string() << endl;
//	tunes.clear();
//	cout << "clear: " << tunes.get_current_song() << endl;
//	cout << "size: " << tunes.get_size() << endl;
//
//
//
//}