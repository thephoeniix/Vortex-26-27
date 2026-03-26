

# 📘 Introducción a Git y Control de Versiones

<p align="center">
  <img src="https://media.giphy.com/media/kH1DBkPNyZPOk0BxrM/giphy.gif" width="400"/>
</p>

---

## 🚀 ¿Qué es Git?

Git es un sistema de control de versiones que permite:

* 📂 Guardar historial de cambios
* 👥 Trabajar en equipo
* ⏪ Volver a versiones anteriores
* 🔒 Proteger tu código

---

## 🛠️ Instalación

<p align="center">
  <img src="https://media.giphy.com/media/ZVik7pBtu9dNS/giphy.gif" width="400"/>
</p>

1. Descargar: [https://git-scm.com](https://git-scm.com)
2. Instalar con opciones por defecto
3. Verificar:

```bash
git --version
```

💡 Si ves un número → todo bien

---

## ⚙️ Configuración inicial

```bash
git config --global user.name "Tu Nombre"
git config --global user.email "tu@email.com"
```

💡 Git usará estos datos en tus commits

---

## 📁 Crear repositorio

<p align="center">
  <img src="https://media.giphy.com/media/QssGEmpkyEOhBCb7e1/giphy.gif" width="400"/>
</p>

```bash
cd nuevo_proyecto
git init
```

---

## 🔄 Flujo básico

```bash
git add .
git commit -m "Mi cambio"
```

💡 Flujo:

* Editas → `add` → `commit`

---

## 🔍 Comandos útiles

```bash
git status   # estado
git log      # historial
git diff     # cambios
```

---

## 🌿 Ramas

```bash
git branch mi-rama
git checkout mi-rama
```

💡 Trabaja sin romper el código principal

---

## 🔀 Merge

```bash
git checkout main
git merge mi-rama
```

---

## ☁️ Subir a GitHub

```bash
git remote add origin URL
git push -u origin main
```

---

## 📥 Clonar repositorio

```bash
git clone URL
```

---

## 👥 Trabajo en equipo

```bash
git pull
git checkout -b mi-rama
git add .
git commit -m "Cambio"
git push origin mi-rama
```

💡 Luego haces Pull Request en GitHub

---

# ⚠️ ERRORES COMUNES

---

## 🔐 Error de login (MUY COMÚN)

```bash
Username for 'https://github.com':
Password for 'https://github.com':
```

👉 GitHub ya NO usa contraseña

---

## ❌ Solución 1: Token

1. [https://github.com/settings/tokens](https://github.com/settings/tokens)
2. Crear token
3. Usarlo como contraseña

---

## ✅ Solución 2 (MEJOR): SSH 🚀

<p align="center">
  <img src="https://media.giphy.com/media/LmNwrBhejkK9EFP504/giphy.gif" width="400"/>
</p>

### 1. Cambiar repo a SSH

```bash
git remote set-url origin git@github.com:TU_USUARIO/TU_REPO.git
```

---

### 2. Verificar

```bash
git remote -v
```

---

### 3. Push

```bash
git push
```

---

## 🎯 Resultado

* ❌ Sin usuario
* ❌ Sin token
* ✅ Automático

---

## ⚠️ Primera vez

```bash
The authenticity of host 'github.com' can't be established...
```

👉 Escribe:

```bash
yes
```

---

## 🧠 Conflictos

```bash
git add .
git commit -m "Conflicto resuelto"
```

---

## 📌 Buenas prácticas

* ✔️ Commits frecuentes
* ✔️ Mensajes claros
* ✔️ Usar ramas
* ❌ No usar `main` directo

---

## 📚 Cheat Sheet

```bash
git init
git add .
git commit -m "mensaje"
git push
git pull
git branch
git checkout
git merge
```

---

## 🎯 Conclusión

Git = herramienta esencial 🚀
Te ayuda a trabajar mejor, más seguro y en equipo.



