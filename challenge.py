# /*
# online cloud lib sys | basically amazon kindle

# cloud reading application

# few things that we are looking for

# 1. each user has a library of books that they can add or delete
# 2. reading application remmebers where user left whilst reading
# 3. users can set book as active i.e currently reading
# 4. reading application only remmembers a page at a time
# */

# quick notes
# user -> class (auth, lib, active)
# user management -> class (manages users, auth, managing duplicate creds)
# book -> class (current active page, partitioning text)
# book management -> (complete library, record of books currently lended or 
# sold to diff users, manages all the databse on books)

from __future__ import annotations
import hashlib
from datetime import datetime


class Book:
    def __init__(self, title, author, content, publication, pub_date) -> None:
        self.title = title
        self.author = author
        self.content = content
        self.publication = publication
        self.pub_date = pub_date
        self.label_information = [
            self.title,
            self.author,
            self.content,
            self.publication,
            self.pub_date,
        ]
        self.active_page = 0

    def initialize_book_pdf(self, text_per_page):
        self.page_list = []
        self.pages = 0
        cur_content = ""
        for icount, text in enumerate(self.content.split(" ")):
            cur_content += text
            if icount % text_per_page == 0:
                self.page_list.append(cur_content)
                cur_content = ""
                self.pages += 1

        return self.page_list

    def __eq__(self, other_book: Book) -> bool:
        if isinstance(other_book, Book):
            raise (
                f"Can't compare a Book object with an object of type, {type(other_book)}"
            )

        return self.label_information == other_book.label_information


class BookManager:
    def __init__(self, books: list[Book], text_per_page) -> None:
        self.total_books = books
        self.text_per_page = text_per_page

    def register_sale(self, book_info, user: User):
        new_book = Book(*book_info)

        for ebook in self.total_books:
            if ebook == new_book:
                new_book.initialize_book_pdf()
                user.library.append(new_book)

        raise Exception(f"Following book; {book_info} is not currently available!")


class User:
    def __init__(self, userid, password) -> None:
        self.userid = userid
        self.password_hash = hashlib.sha1(password)
        self.user_ledger = {self.userid: self.password_hash}
        self.library = []

    def __eq__(self, other: User) -> bool:
        return self.userid == other.userid

    def print_booklist(self):
        print([(i, book.title) for i, book in enumerate(self.library)])

    def read_book(self, book_ind):
        book: Book = self.library[book_ind]
        print(book.page_list[book.active_page])
        book.active_page += 1
        self.library[book_ind] = book


class UserManager:
    def __init__(self) -> None:
        self.user_accounts: list[User] = []

    def register_account(self, new_account: User):
        for acc in self.user_accounts:
            if acc == new_account:
                # we are only checking for similar usernames not passwords
                raise Exception("Account with same user_id already exists")

        self.user_accounts.append(new_account)

    def authentication(self, userid: str, password: str):
        pw_hash = hashlib.sha1(password)
        for acc in self.user_accounts:
            uid, h = acc.user_ledger.items()
            if uid == userid and pw_hash == h:
                return acc

        return None


def main():
    u1 = User()
    u2 = User()


if __name__ == "__main__":
    main()
