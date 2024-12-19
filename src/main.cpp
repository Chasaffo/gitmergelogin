#include <iostream>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Funktion för att visa inloggningsfönstret
void ShowLoginWindow(char* username, char* password) {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;
    ImGui::Begin("Login", nullptr, window_flags);

    ImGui::Text("Username");
    ImGui::InputText("##username", username, IM_ARRAYSIZE(username));

    ImGui::Text("Password");
    ImGui::InputText("##password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

    if (ImGui::Button("Log in"))
    {
        std::cout << "Username: " << username << std::endl;
        std::cout << "Password: " << password << std::endl;
    }
    ImGui::Text("\nCreate account");
    ImGui::Text("Forgot password");
    ImGui::End();
}

int main() {

    if (!glfwInit())
    {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(
        800,
        600,
        "Test App",
        NULL,
        NULL
    );

    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImGui::StyleColorsLight();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    char username[128] = "";
    char password[128] = "";

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Anropa funktionen för att visa inloggningsfönstret
        ShowLoginWindow(username, password);

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w,
            clear_color.y * clear_color.w,
            clear_color.z * clear_color.w,
            clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
