## Tóm tắt State Machine Pattern

**State Machine Pattern** (Mẫu hình máy trạng thái) là một **mẫu thiết kế hành vi** giúp một đối tượng thay đổi hành vi của nó một cách có tổ chức khi **trạng thái nội bộ** của nó thay đổi. Thay vì sử dụng các câu lệnh điều kiện `if-else` hoặc `switch-case` phức tạp để xác định hành vi dựa trên trạng thái hiện tại, mẫu này **tách biệt logic của mỗi trạng thái** vào các "đối tượng" hoặc module riêng biệt. Điều này làm cho mã nguồn dễ quản lý, mở rộng và ít lỗi hơn.

---

### Cơ chế Hoạt động

Mẫu State Machine Pattern hoạt động dựa trên ba thành phần chính:

1.  **Context (Ngữ cảnh):**
    * Đây là đối tượng mà hành vi của nó thay đổi. Nó **duy trì một tham chiếu** đến đối tượng **State** hiện tại của nó.
    * Mọi yêu cầu hoặc sự kiện từ bên ngoài được Context **ủy quyền (delegate)** cho đối tượng State hiện tại để xử lý. Context không tự biết logic của từng trạng thái; nó chỉ biết trạng thái nào đang hoạt động và yêu cầu trạng thái đó xử lý.

2.  **State Interface (Giao diện Trạng thái):**
    * Đây là một giao diện (trong C có thể là `struct` chứa các con trỏ hàm) định nghĩa **tất cả các hành động/phương thức** mà một đối tượng Context có thể ủy quyền cho các đối tượng State cụ thể.
    * Tất cả các trạng thái cụ thể phải thực hiện giao diện này, đảm bảo rằng Context luôn có thể gọi các hành động này mà không cần biết trạng thái cụ thể nào đang xử lý.

3.  **Concrete State (Trạng thái Cụ thể):**
    * Mỗi lớp (hoặc tập hợp hàm trong C) **triển khai giao diện State** cho một trạng thái cụ thể.
    * Nó chứa **toàn bộ logic hành vi** khi đối tượng Context ở trong trạng thái đó.
    * Quan trọng hơn, các trạng thái cụ thể này cũng **chịu trách nhiệm cho việc chuyển đổi trạng thái**: chúng quyết định khi nào và làm thế nào để Context chuyển sang một trạng thái khác dựa trên các sự kiện hoặc điều kiện xảy ra. Điều này được thực hiện bằng cách gọi một phương thức trên Context để thiết lập trạng thái mới.

---

### Tóm tắt Luồng Hoạt động:

1.  **Khởi tạo:** Đối tượng **Context** được tạo và khởi tạo với một **Concrete State** mặc định (ví dụ: trạng thái `STOPPED` cho trình phát nhạc).
2.  **Xử lý Sự kiện:** Khi một sự kiện xảy ra (ví dụ: người dùng nhấn nút `PLAY`), Context nhận sự kiện đó.
3.  **Ủy quyền:** Context không tự xử lý sự kiện. Thay vào đó, nó **gọi phương thức tương ứng** trên đối tượng **State** hiện tại của mình (ví dụ: `player->currentStateHandler->pressPlay(player)`).
4.  **Hành vi theo Trạng thái:** Đối tượng **Concrete State** hiện tại sẽ thực hiện hành vi cụ thể của nó dựa trên sự kiện và trạng thái hiện tại.
5.  **Chuyển đổi Trạng thái:** Nếu cần, đối tượng **Concrete State** sẽ gọi một phương thức trên **Context** (ví dụ: `setPlayerState(player, STATE_PAUSED)`) để thay đổi trạng thái hiện tại của Context sang một **Concrete State** khác. Lúc này, Context sẽ cập nhật tham chiếu `currentStateHandler` của nó.
6.  **Lặp lại:** Chu trình này tiếp tục khi các sự kiện mới đến, và Context sẽ luôn ủy quyền xử lý cho đối tượng State mà nó đang trỏ tới.

Mẫu này loại bỏ các phụ thuộc trực tiếp giữa Context và các trạng thái cụ thể bằng cách sử dụng giao diện, giúp hệ thống linh hoạt và dễ thay đổi hơn nhiều.