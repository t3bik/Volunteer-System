
# Gönüllü Randevu Sistemi

## Projenin Amacı
Bu proje, gönüllülerin etkinliklere katılımını kolaylaştırmak ve organizatörlerin etkinlikleri yönetmesini sağlamak amacıyla geliştirilmiştir.
Kullanıcılar sisteme kaydolabilir, etkinlik oluşturabilir, mevcut etkinliklerdeki görevleri arayabilir ve veriler kalıcı olarak saklanır.

## Gerekli Kütüphaneler ve Bağımlılıklar
- **stdio.h**: Giriş ve çıkış işlemleri için.
- **stdlib.h**: Bellek yönetimi ve sayısal dönüşümler için.
- **string.h**: Karakter dizisi işlemleri için.

---

# Volunteer Appointment System

## Purpose of the Project
This project is designed to facilitate volunteer participation in events and help organizers manage their events.
Users can register in the system, create events, search for tasks in existing events, and data is persistently stored.

## Required Libraries and Dependencies
- **stdio.h**: For input and output operations.
- **stdlib.h**: For memory management and numeric conversions.
- **string.h**: For string manipulations.

---

## Kurulum ve Çalıştırma / Setup and Run

### Kurulum / Setup
1. GCC'nin yüklü olduğundan emin olun (Verify GCC is installed):
   ```bash
   gcc --version
   ```

2. GCC yüklü değilse yükleyin (Install GCC if not installed):
   - **Linux:** `sudo apt-get install gcc`
   - **MacOS (Homebrew):** `brew install gcc`
   - **Windows:** MinGW veya Cygwin kullanarak yükleyin.

### Çalıştırma / Run
1. Kodu derleyin (Compile the code):
   ```bash
   gcc volunteer_system_with_storage.c -o volunteer_system
   ```

2. Programı çalıştırın (Run the program):
   ```bash
   ./volunteer_system
   ```

---

## Kullanım / Usage
- **Kullanıcı Kaydı (User Registration):** Kullanıcılar gönüllü veya organizatör olarak sisteme kaydolabilir.
- **Etkinlik Oluşturma (Create Events):** Yeni etkinlikler oluşturabilir ve görevler tanımlayabilirsiniz.
- **Etkinlik ve Görev Arama (Search Events and Tasks):** Mevcut etkinlikleri ve görevleri listeleyebilirsiniz.
- **Çıkış (Exit):** Programı güvenli bir şekilde sonlandırabilirsiniz.

---

## Notlar / Notes
- Programın çalışması için `veriler.txt` dosyasına yazma ve okuma izni olmalıdır.
- Kod, "Algoritma ve Programlama 1" ders içeriğine uygun şekilde yazılmıştır.
