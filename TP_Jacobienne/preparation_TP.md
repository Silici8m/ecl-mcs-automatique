# Préparation au TP — À faire **avant** le cours

> **Éditeur de code recommandé :** si vous n'en avez pas, installez [Visual Studio Code](https://code.visualstudio.com/) (gratuit, Windows/Linux) avec l'extension Python.

---

## 1. Installer Python 3.10

> Si vous avez déjà Python 3.10, passez à l'étape 2.

### Windows
1. Téléchargez l'installeur sur [python.org/downloads](https://www.python.org/downloads/release/python-31011/)  
   → Choisissez **Windows installer (64-bit)**
2. Lancez l'installeur, **cochez "Add Python to PATH"**, puis cliquez *Install Now*
3. Vérifiez dans un terminal (cmd ou PowerShell) :
   ```
   py -3.10 --version
   ```

### Linux
```bash
sudo apt update
sudo apt install python3.10 python3.10-venv python3.10-dev
python3.10 --version
```

---

## 2. Installer Tkinter pour Python 3.10

### Windows
Tkinter est inclus par défaut dans l'installeur Python. Vérifiez :
```
py -3.10 -c "import tkinter; print('OK')"
```

### Linux
```bash
sudo apt install python3.10-tk
python3.10 -c "import tkinter; print('OK')"
```

Si la commande affiche `OK`, vous pouvez passer à l'étape suivante.

---

## 3. Créer le dossier du TP et l'environnement virtuel

1. Créez un dossier pour le TP (par exemple `tp_emio`) et placez-vous dedans :

   **Windows (PowerShell)**
   ```powershell
   mkdir tp_emio
   cd tp_emio
   ```

   **Linux**
   ```bash
   mkdir tp_emio && cd tp_emio
   ```

2. Créez l'environnement virtuel avec Python 3.10 :

   **Windows (PowerShell)**
   ```powershell
   py -3.10 -m venv venv
   ```

   **Linux**
   ```bash
   python3.10 -m venv venv
   ```

3. Activez l'environnement virtuel :

   **Windows (PowerShell)**
   ```powershell
   venv\Scripts\activate
   ```

   **Linux**
   ```bash
   source venv/bin/activate
   ```

   > Votre terminal doit afficher `(venv)` au début de la ligne.

   > **À retenir :** cette commande d'activation est à relancer à chaque fois que vous ouvrez un nouveau terminal, depuis le dossier `tp_emio`.

---

## 4. Installer les dépendances

Copiez les fichiers `requirements.txt` et `gui_emio.py` dans le dossier `tp_emio`, puis :

```bash
pip install -r requirements.txt
```

---

## 5. Tester le fichier GUI

```bash
python gui_emio.py
```

Une fenêtre doit s'ouvrir. Si c'est le cas, **vous êtes prêt(e) pour le cours** ✓

---

## Résolution de problèmes fréquents

| Problème | Solution |
|---|---|
| `py -3.10` non reconnu (Windows) | Réinstallez Python 3.10 en cochant "Add to PATH" |
| `No module named tkinter` (Linux) | Relancez `sudo apt install python3.10-tk` |
| `(venv)` n'apparaît pas | Vérifiez que vous avez bien exécuté la commande d'activation |
| Erreur à l'installation du `requirements.txt` | Vérifiez que `(venv)` est actif et envoyez le message d'erreur à l'enseignant |
