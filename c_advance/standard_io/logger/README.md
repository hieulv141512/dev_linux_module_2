## Tóm tắt chương trình

Chương trình C này là một ứng dụng minh họa cho một **module ghi nhật ký (logger) tùy chỉnh**. Mục đích chính của nó là trình bày cách xây dựng một hệ thống logger linh hoạt và mạnh mẽ, có khả năng:

* **Ghi log ra nhiều đích**: In thông điệp log ra **console** (màn hình) và tùy chọn ghi vào một **file văn bản**.
* **Lọc theo cấp độ nghiêm trọng**: Chỉ ghi lại các thông điệp có **mức độ ưu tiên (level)** nhất định trở lên (ví dụ: chỉ lỗi, không ghi debug).
* **Tự động thêm ngữ cảnh**: Mỗi thông điệp log sẽ tự động được bổ sung **thời gian (timestamp)**, **tên file nguồn** và **số dòng code** nơi lệnh log được gọi.
* **Hỗ trợ đa thể hiện (Multiple Instances)**: Có thể tạo và quản lý **nhiều đối tượng logger độc lập** trong cùng một ứng dụng, mỗi đối tượng có cấu hình riêng về file log và mức độ lọc.

Nói cách khác, chương trình này cho thấy một cách tiếp cận thực tế để thay thế `printf()` đơn thuần bằng một hệ thống ghi log có tổ chức và khả năng tùy biến cao, rất hữu ích trong phát triển phần mềm nhúng hoặc các ứng dụng lớn.

## Chương trình hoạt động ra sao?

Chương trình hoạt động dựa trên một module `logger` được thiết kế cẩn thận, bao gồm file header (`logger.h`) và file triển khai (`logger.c`).

1.  **Khởi tạo Logger**:
    * Trong `main.c`, chương trình bắt đầu bằng cách gọi `loggerInit()` để khởi tạo một hoặc nhiều **thể hiện (instance)** của logger.
    * Mỗi lần gọi `loggerInit()` sẽ cấp phát bộ nhớ cho một `struct Logger` mới, thiết lập file log đầu ra (nếu có) và mức lọc log ban đầu. Ví dụ:
        * `logger`: Ghi vào `main.log`, mức lọc `LOG_INFO`.
        * `otherLogger`: Chỉ ghi ra console (không ghi file), mức lọc `LOG_WARNING`.
    * Hàm `loggerInit()` trả về một **con trỏ** tới thể hiện logger vừa tạo. Nếu không tạo được (ví dụ: hết bộ nhớ, không mở được file), nó sẽ trả về `NULL`.

2.  **Ghi thông điệp Log**:
    * Chương trình sử dụng các **macros tiện lợi** như `LOG_INFO()`, `LOG_ERROR()`, `LOG_DEBUG()`, v.v., để gửi thông điệp log.
    * Các macros này tự động truyền **con trỏ logger** (`logger` hoặc `otherLogger`), **cấp độ log** (ví dụ: `LOG_INFO`), **tên file nguồn** (`__FILE__`) và **số dòng code** (`__LINE__`) tới hàm nội bộ `loggerLog()`.
    * Hàm `loggerLog()`:
        * **Kiểm tra mức lọc**: Đầu tiên, nó so sánh cấp độ của thông điệp đang muốn ghi với `minLevel` của logger đó. Nếu thông điệp có mức độ ưu tiên thấp hơn (số lớn hơn), nó sẽ bị bỏ qua.
        * **Lấy Timestamp**: Lấy thời gian hiện tại của hệ thống và định dạng nó thành chuỗi `YYYY-MM-DD HH:MM:SS`.
        * **Lấy Tên File ngắn gọn**: Tách tên file gốc (ví dụ: `main.c`) từ đường dẫn đầy đủ (`/path/to/main.c`).
        * **Định dạng Chuỗi Log**: Ghép timestamp, cấp độ log, tên file/số dòng và thông điệp tùy chỉnh của người dùng vào một chuỗi duy nhất theo định dạng chuẩn: `[YYYY-MM-DD HH:MM:SS] [LEVEL] [FILENAME:LINE] - Message`.
        * **Ghi ra đầu ra**:
            * Nếu thông điệp có mức độ `LOG_ERROR` trở xuống (nghiêm trọng hơn), nó được ghi ra **stderr**.
            * Các thông điệp khác được ghi ra **stdout**.
            * Nếu logger được cấu hình ghi file, thông điệp cũng được ghi vào file tương ứng. Hàm `fflush()` được sử dụng để đảm bảo dữ liệu được ghi ra ngay lập tức.

3.  **Thay đổi mức lọc Log động**:
    * Chương trình minh họa việc gọi `setLogLevel()` để thay đổi `minLevel` của một logger tại thời điểm chạy. Điều này cho phép điều chỉnh mức độ chi tiết của log mà không cần biên dịch lại chương trình.

4.  **Giải phóng tài nguyên**:
    * Cuối cùng, trước khi kết thúc chương trình, `destroyLogger()` được gọi cho mỗi thể hiện logger đã tạo. Hàm này sẽ đóng file log (nếu có) và giải phóng bộ nhớ đã cấp phát cho `struct Logger`, tránh rò rỉ bộ nhớ.

---

## Cần lưu ý những gì?

1.  **Quản lý bộ nhớ**:
    * `loggerInit()` sử dụng `malloc()` để cấp phát bộ nhớ cho `struct Logger`. Do đó, người dùng **phải gọi `destroyLogger()`** để giải phóng bộ nhớ này khi logger không còn cần thiết, tránh rò rỉ bộ nhớ.
    * Nếu `loggerInit()` trả về `NULL`, nghĩa là có lỗi (ví dụ: không đủ bộ nhớ, không mở được file log). Chương trình gọi phải xử lý tình huống này.

2.  **An toàn chuỗi (`snprintf`, `vsnprintf`)**:
    * Chương trình sử dụng `snprintf` và `vsnprintf` để định dạng chuỗi. Đây là các hàm an toàn, ngăn chặn tràn bộ đệm bằng cách giới hạn số ký tự ghi vào. Điều này rất quan trọng để tránh các lỗ hổng bảo mật.

3.  **Thread Safety (An toàn luồng)**:
    * Phiên bản logger này **chưa có cơ chế an toàn luồng (thread-safe)**. Nếu bạn sử dụng logger này trong một ứng dụng đa luồng, nhiều luồng cùng ghi log đồng thời có thể dẫn đến tình trạng tranh chấp tài nguyên (race condition) và làm hỏng log file hoặc gây ra hành vi không mong muốn. Để khắc phục, bạn cần thêm mutex (ví dụ: `pthread_mutex_t` trên POSIX) để bảo vệ các thao tác ghi log.

4.  **Hiệu suất I/O (`fflush`)**:
    * Việc gọi `fflush()` sau mỗi lần `fprintf()` đảm bảo rằng dữ liệu được ghi ra ngay lập tức, rất hữu ích cho việc gỡ lỗi hoặc khi ứng dụng có thể gặp sự cố đột ngột. Tuy nhiên, nó cũng có thể ảnh hưởng đến hiệu suất, đặc biệt là trong các ứng dụng ghi log với tần suất rất cao. Trong môi trường nhạy cảm về hiệu suất, có thể cân nhắc một cơ chế đệm (buffering) hoặc ghi log không đồng bộ.

5.  **Cấu trúc thư mục (Include Paths)**:
    * Đảm bảo rằng trình biên dịch có thể tìm thấy `logger.h` khi biên dịch `logger.c` và `main.c`. Thông thường, bạn sẽ đặt các file này trong cùng thư mục hoặc sử dụng cờ biên dịch `-I` để chỉ định đường dẫn include.

6.  **Tính di động (Portability)**:
    * Hàm `getFilenameFromPath` xử lý cả dấu `/` (Linux/macOS) và `\` (Windows). Tuy nhiên, các hàm thời gian (`time`, `localtime`) có thể có hành vi hơi khác nhau trên các hệ điều hành khác nhau, nhưng nhìn chung là đủ di động cho mục đích này.

7.  **Sử dụng Macros**:
    * Các macros (`LOG_INFO`, `LOG_ERROR`, v.v.) là một cách tiện lợi để người dùng gọi hàm log mà không cần tự cung cấp `__FILE__` và `__LINE__`. Tuy nhiên, cần hiểu rằng macros thực hiện thay thế văn bản đơn giản và không có kiểm tra kiểu như hàm thông thường.