

# 📘 Introducción a Git y Control de Versiones

Este repositorio contiene una guía básica para aprender a usar Git y GitHub desde cero.
Está diseñado para que cualquier persona pueda seguir los pasos fácilmente, incluso sin experiencia previa.

📄 Basado en el material: /Introduccion_Git.pdf

---

## 🚀 ¿Qué es Git?

Git es un sistema de control de versiones que permite:

* Guardar el historial completo de cambios
* Trabajar en equipo sin conflictos
* Recuperar versiones anteriores
* Proteger tu código ante errores o pérdidas

---

## 🛠️ Instalación

1. Descargar Git desde: [https://git-scm.com](https://git-scm.com)
2. Instalar con las opciones por defecto
3. Verificar instalación:

```bash
git --version
```

---

## ⚙️ Configuración inicial

Antes de usar Git, configura tu identidad:

```bash
git config --global user.name "Tu Nombre"
git config --global user.email "tu@email.com"
```

---

## 📁 Crear tu primer repositorio

```bash
cd ruta/a/tu/proyecto
git init
```

---

## 🔄 Flujo básico de trabajo

1. Modificar archivos
2. Agregar cambios:

```bash
git add .
```

3. Guardar cambios (commit):

```bash
git commit -m "Descripción del cambio"
```

---

## 🔍 Comandos útiles

```bash
git status   # Ver estado
git log      # Ver historial
git diff     # Ver cambios
```

---

## 🌿 Trabajar con ramas

Crear una rama:

```bash
git branch mi-rama
```

Cambiar de rama:

```bash
git checkout mi-rama
```

---

## 🔀 Merge (Unir ramas)

```bash
git checkout main
git merge mi-rama
```

---

## ☁️ Subir proyecto a GitHub

1. Conectar repositorio:

```bash
git remote add origin URL
```

2. Subir cambios:

```bash
git push -u origin main
```

---

## 📥 Clonar repositorio

```bash
git clone URL
```

---

## 👥 Trabajo en equipo

Flujo recomendado:

```bash
git pull
git checkout -b mi-rama
# haces cambios
git add .
git commit -m "Mi cambio"
git push origin mi-rama
```

Luego haces un **Pull Request en GitHub**.

---

## ⚠️ Errores comunes y soluciones

### ❌ Error al iniciar sesión en GitHub

Si tienes problemas de autenticación (muy común):

👉 GitHub ya no usa contraseña, usa **Personal Access Token (PAT)**

### ✅ Solución:

1. Ir a: [https://github.com/settings/tokens](https://github.com/settings/tokens)
2. Crear un **Personal Access Token**
3. Usar ese token como contraseña al hacer `git push`

---

## 🔐 Error al iniciar sesión (Token / Password)

Si al hacer `git push` te pide usuario y contraseña, y falla:

```bash
Username for 'https://github.com':
Password for 'https://github.com':
```

👉 Esto pasa porque GitHub ya no usa contraseñas normales.

---

### ❌ Solución 1: Usar Personal Access Token (PAT)

1. Ve a: [https://github.com/settings/tokens](https://github.com/settings/tokens)
2. Genera un **Personal Access Token**
3. Usa ese token como contraseña

---

### ✅ Solución 2 (RECOMENDADA): Usar SSH 🔥

Con SSH ya no necesitas tokens ni contraseñas.

#### 1. Cambia tu repositorio a SSH:

```bash
git remote set-url origin git@github.com:TU_USUARIO/TU_REPO.git
```

#### 2. Verifica:

```bash
git remote -v
```

Debe aparecer:

```bash
origin  git@github.com:TU_USUARIO/TU_REPO.git (fetch)
origin  git@github.com:TU_USUARIO/TU_REPO.git (push)
```

#### 3. Haz push:

```bash
git push
```

---

### 🎯 Resultado

* ❌ No más usuario
* ❌ No más tokens
* ✅ Conexión automática segura

---

### ⚠️ Nota

La primera vez puede pedir confirmación:

```bash
The authenticity of host 'github.com' can't be established...
```

Solo escribe:

```bash
yes
```

---

## 💡 Recomendación

Usa **SSH siempre** para evitar problemas de autenticación.


## 🧠 Conflictos de merge

Si ocurre un conflicto:

1. Git marcará el archivo
2. Edita manualmente el contenido
3. Luego:

```bash
git add .
git commit -m "Resuelto conflicto"
```

---

## 📌 Buenas prácticas

* ✔️ Hacer commits frecuentes
* ✔️ Escribir mensajes claros
* ✔️ Usar ramas
* ❌ No trabajar directo en `main`
* ❌ No subir archivos innecesarios

---

## 📚 Comandos básicos (resumen)

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

Git es una herramienta esencial para cualquier programador.
Te permite trabajar mejor en equipo, mantener tu código seguro y tener control total sobre tus cambios.



