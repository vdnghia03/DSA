#include <stdio.h>

// Binary Search đệ quy
int binarySearchRecursive(int arr[], int left, int right, int target) {
    if (left > right) {
        return -1; // Không tìm thấy phần tử trong mảng
    }

    int mid = (left + right) / 2;

    if (arr[mid] == target) {
        return mid; // Phần tử được tìm thấy
    } else if (arr[mid] > target) {
        return binarySearchRecursive(arr, left, mid - 1, target); // Tìm kiếm nửa trái của mảng
    } else {
        return binarySearchRecursive(arr, mid + 1, right, target); // Tìm kiếm nửa phải của mảng
    }
}

// Phân tích hàm đệ quy theo quy trình bốn bước:
// 1. Xác định điểm dừng: Khi left > right (1), khi arr[mid] == val (2)
//   
//2. với (1)  Trong trường hợp này, trả về -1 để thể hiện không tìm thấy phần tử trong mảng, vói (2) trả về giá trị mid.
//3. với left == right 
//    Điều này áp dụng trong hai trường hợp:
//    - Nếu arr[mid] == target, trả về mid để thể hiện phần tử được tìm thấy.
//    - Nếu arr[mid] > target,  trả về -1
//    - Nếu arr[mid] < target, trả về -1
//4.với left >= right 
//    Điều này áp dụng trong hai trường hợp:
//    - Nếu arr[mid] == target, trả về mid để thể hiện phần tử được tìm thấy.
//    - Nếu arr[mid] > target,  gọi đệ quy tìm kiếm trong nửa trái của mảng
//    - Nếu arr[mid] < target,  gọi đệ quy tìm kiếm trong nửa phải của mảng.

int main() {
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 12;

    int result = binarySearchRecursive(arr, 0, n - 1, target);

    if (result == -1) {
        printf("Phan tu %d khong tim thay trong mang.\n", target);
    } else {
        printf("Phan tu %d tim thay tai vi tri %d trong mang.\n", target, result);
    }

    return 0;
}
