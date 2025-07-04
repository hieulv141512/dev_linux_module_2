## Chức năng Chính của Chương trình Quản lý Thư viện

Chương trình C này triển khai một hệ thống quản lý thư viện cơ bản, cho phép người dùng thực hiện các thao tác quản lý sách điển hình.

Các chức năng chính có thể được tóm tắt như sau:

* **Quản lý Thư viện**:
    * **Khởi tạo Thư viện**: Tạo một đối tượng `Library` mới để chứa và quản lý các cuốn sách.
    * **Phá hủy Thư viện**: Giải phóng tất cả bộ nhớ đã cấp phát cho thư viện và các cuốn sách bên trong nó khi không còn sử dụng, ngăn chặn rò rỉ bộ nhớ.
* **Quản lý Sách**:
    * **Tạo Sách**: Khởi tạo các đối tượng `Book` riêng lẻ với các thuộc tính như tên sách (`title`), tác giả (`author`), mã số ISBN (`isbn`), và trạng thái mượn (`isBorrowed`).
    * **Thêm Sách vào Thư viện**: Thêm một cuốn sách mới vào thư viện. Chương trình bao gồm logic để ngăn việc thêm các cuốn sách trùng lặp (dựa trên ISBN).
    * **Tìm Sách**: Tìm kiếm một cuốn sách cụ thể trong thư viện dựa trên mã số ISBN của nó.
    * **Cập nhật Thông tin Sách**: Cho phép sửa đổi trạng thái mượn của sách hoặc cập nhật thông tin về tên sách và tác giả.
    * **Xóa Sách khỏi Thư viện**: Xóa một cuốn sách khỏi thư viện dựa trên mã số ISBN.
    * **Liệt kê Sách**: Hiển thị danh sách tất cả các cuốn sách hiện có trong thư viện cùng với thông tin chi tiết của chúng.

* **Mô phỏng Thao tác**:
    * Chương trình `main.c` mô phỏng một luồng hoạt động điển hình bao gồm việc tạo thư viện, thêm nhiều sách, tìm kiếm, cập nhật trạng thái (mượn/trả), và xóa sách, thể hiện khả năng của hệ thống quản lý.
    * Nó cũng bao gồm các trường hợp kiểm tra lỗi như cố gắng thêm sách trùng lặp, cập nhật/xóa sách không tồn tại để xác minh tính mạnh mẽ của các chức năng.

Tóm lại, chương trình này cung cấp một khuôn khổ cơ bản cho việc quản lý các đối tượng sách trong một cấu trúc thư viện, tập trung vào các thao tác CRUD (Create, Read, Update, Delete) và quản lý bộ nhớ.

---

## How to run
- Build: `make all`
- Run: `make run`
- Clean: `make clean`