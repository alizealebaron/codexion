<p align="center">
  <img src="https://github.com/alizealebaron/alizealebaron/blob/main/assets/codexion_simple.png" width="120"/> 
</p>
<h3 align="center">
  <em>Master the race for resources before the deadline masters you.</em>
</h3>

---

<div align="center">
  <p>
      <img src="https://img.shields.io/badge/score-100%20%2F%20100-success?style=for-the-badge" />
      <img src="https://img.shields.io/github/languages/count/alizealebaron/codexion?style=for-the-badge&logo=" />
      <img src="https://img.shields.io/github/languages/top/alizealebaron/codexion?style=for-the-badge" />
      <img src="https://img.shields.io/github/last-commit/alizealebaron/codexion?style=for-the-badge" />
  </p>
</div>

## ⚠️ Avant propos

- **Portfolio :** Ce répertoire se concentre sur un seul sujet. Vous pouvez retrouver tous mes projets sur mon [profil](https://github.com/alizealebaron).
- **Sujet :** Conformément aux règles de 42, vous ne trouverez pas le sujet de l'exercice dans ce répertoire.
- **État du projet:** Le code est exactement le même que lorsqu'il est validé. Il ne sera pas mis à jour même s'il contient des erreurs.
- **Aide & Licence :** Ce repertoire est principalement là pour vous aider à faire votre propre code. Évitez de copier / coller sans comprendre le code.

## 🦆 Status

**Commencé le :** 03/02/2026

**Rendu le :** 05/05/2026

## Description

Codexion est un projet de programmation en C explorant les défis de la concurrence et de la synchronisation de ressources.

Le projet simule un endroit où des développeurs (threads) se disputent l'accès à des ressources limitées (dongles USB protégés par des mutex) pour compiler leur code. L'objectif est d'implémenter un algorithme d'ordonnancement robuste (FIFO ou EDF) capable de prévenir les deadlocks, de gérer des temps de refroidissement matériels et d'éviter le "burnout" des développeurs avant l'échéance fixée.

### Points clés du projet :

- **Multi-threading** : Gestion de cycles de vie complexes (compiler, debugger, refactoriser) via pthread.
- **Ordonnancement personnalisé** : Implémentation d'une file de priorité (Heap) pour First In, First Out (fifo) et Earliest Deadline First (edf).
- **Synchronisation fine** : Utilisation de variables de condition et de mutex pour orchestrer l'accès aux dongles partagés sans interblocage.
- **Monitorage temps réel** : Surveillance de la simulation par un thread dédié pour une détection de burnout précise à 10ms près.

## Installation

```bash
# Cloner le projet
git clone https://github.com/alizealebaron/codexion.git
cd codexion

# Compiler le projet
make
```

### Commandes du Makefile

```bash
# Lance le programme avec des paramètres par défaut
make run

# Nettoie les fichiers objets
make clean

# Nettoie les fichiers objets et l'exécutable
make fclean

# Compile à nouveau l'entièreté des fichiers
make re

# Similaire à make
make all
```

### Exécution Basique

```bash
# Utiliser des paramètres par défaut
make run
# Passer vos propres paramètres
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

## Architecture du code

### Arborescence des fichiers
```
codexion/
├── Makefile                  # Automatisation des commandes
├── README.md                 # Explications du projet en anglais
├── README_FR.md              # Explications du projet en français
├── obj/                      # Objet après la compilation
└── coders/
    ├── cleaning/          
    │   └── destroy_mutex.c   
    ├── init/
    │   ├── check_args.c
    │   └── init_struct.c
    ├── parsing/            
    │   ├── manage_dongle.c
    │   ├── manage_thread.c
    │   ├── routines_utils.c
    │   ├── routines.c
    │   ├── scheduler_utils.c
    │   ├── scheduler.c
    │   └── simulation_check.c
    ├── utils/
    │   ├── exit_utils.c
    │   ├── heap_utils.c
    │   ├── print_utils.c
    │   ├── queue_utils.c
    │   └── time_utils.c
	├── codexion.h
    └── codexion.c
```

## Défis rencontrés et solutions

### Prévention des interblocages (Deadlocks)

La solution implémente une prévention des interblocages. Chaque coder doit acquérir deux dongles pour compiler, ce qui crée naturellement un risque de deadlock si non géré correctement.

**Prévention des conditions :**

1. **Exclusion mutuelle** : Les mutex sont utilisés pour garantir l'accès exclusif aux dongles (ressource critique).

2. **Hold and Wait éliminé** : Bien que techniquement utilisé, le problème est résolu par l'**ordre fixe d'acquisition** des ressources. Chaque coder acquiert toujours ses dongles dans le même ordre (basé sur leur ID). La fonction `get_ordered_dongles()` assure que `first` (ID inférieur) est toujours acquis avant `second` (ID supérieur) :

```c
void	get_ordered_dongles(t_coder *coder, t_dongle **first, t_dongle **second)
{
	if (coder->left_dongle->id < coder->right_dongle->id)
	{
		*first = coder->left_dongle;
		*second = coder->right_dongle;
	}
	else
	{
		*first = coder->right_dongle;
		*second = coder->left_dongle;
	}
}
```

3. **Acquisition deux par deux** : Les dongles sont toujours récupéré deux par deux, si l'un des deux ou les deux ne sont pas libre, à ce moment là le coder attendra qu'ils le soient.

4. **Circular Wait éliminé** : Grâce à l'ordre fixe d'acquisition, il y a une relation d'ordre totale sur les ressources (dongles). Aucun cycle n'est possible.

### Prévention du burnout

Deux algorithmes d'ordonnancement équitable sont implémentés :

- **FIFO (First In, First Out)** : Un coder ajouté à la queue doit attendre que tous les coders avant lui aient accès aux dongles. La fonction `wait_for_dongle_fifo()` garantit que seul le premier élément de la queue peut prendre les dongles.

- **EDF (Earliest Deadline First)** : Un heap binaire min-priorité ordonne les coders selon `last_compile_time`. Cette approche favorise les coders qui n'ont pas compilé récemment, évitant la famine systématique.

Lorsqu'un coder libère les dongles, un `pthread_cond_broadcast()` réveille tous les threads en attente pour qu'ils réessaient d'acquérir les ressources selon leur ordre de priorité.

### Gestion du délai de refroidissement (Cooldown)

Après chaque compilation, les dongles sont mis à jour avec un temps de cooldown :

```c
coder->left_dongle->cooldown = time + coder->data->dongle_cooldown;
coder->right_dongle->cooldown = time + coder->data->dongle_cooldown;
```

Avant d'acquérir un dongle, la fonction `take_dongle()` vérifie que le cooldown est écoulé. Les coders qui tentent d'accéder à un dongle en cooldown sont bloqués et attendent la prochaine notification.

### Détection de burnout précise

Un thread moniteur dédié (`main_routine`) scrute l'état de chaque coder **tous les 100 microsecondes**. Il vérifie pour chaque coder si le temps écoulé depuis la dernière compilation dépasse `time_to_burnout` :

```c
if (finish == 0 && (get_time() - last_compile > data->time_to_burnout))
{
	print_message(data, data->coders[i].number, LOG_BURNS_OUT);
	return (1);	// Burnout détecté
}
```

Cette fréquence de scrutation (100 µs) permet une détection précise à environ 10 ms près, bien inférieure à la plupart des délais de burnout.

## Mécanismes de synchronisation des threads

### Primitives de synchronisation utilisées

L'implémentation utilise trois primitives principales pour orchestrer la concurrence :

#### 1. **Mutex (`pthread_mutex_t`)**

- **Mutex des dongles** : Chaque dongle dispose d'un `lock` mutex pour protéger son état (cooldown, is_lock).
- **Mutex des coders** : Chaque coder a un `lock` mutex pour protéger ses données mutantes (last_compile_time, has_finished, compiles_done).
- **Mutex d'impression** : `print_mutex` sérialise tous les accès à stdout.
- **Mutex principal** : `main_mutex` protège l'état global de la simulation (is_sim_active).
- **Mutex de la queue/heap** : `queue_ctrl.mutex` et `heap->mutex` protègent les structures de file.

#### 2. **Variables de condition (`pthread_cond_t`)**

- **Condition de queue** : `queue_ctrl.cond` notifie les coders en attente quand un dongle se libère (FIFO).
- **Condition de heap** : `heap->cond` notifie les coders en attente quand un dongle se libère (EDF).

### Coordination de l'accès aux ressources partagées

#### Accès aux dongles

Chaque dongle est protégé par son propre mutex. L'acquisition se fait en deux étapes avec l'ordre fixe :

```c
int	take_dongle(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	get_ordered_dongles(coder, &first, &second);
	pthread_mutex_lock(&first->lock);
	if (first->cooldown <= get_time()) {
		pthread_mutex_lock(&second->lock);
		if (second->cooldown <= get_time()) {
			// Marquer les dongles comme utilisés
			coder->left_dongle->is_lock = 1;
			coder->right_dongle->is_lock = 1;
			pthread_mutex_unlock(&second->lock);
			pthread_mutex_unlock(&first->lock);
			return (1);	// Succès
		}
		pthread_mutex_unlock(&second->lock);
	}
	pthread_mutex_unlock(&first->lock);
	return (0);	// Impossible d'acquérir
}
```

**Prévention des conditions de course** :
- L'ordre fixe élimine les deadlocks entre threads rivaux.
- Les vérifications de cooldown sont protéges par les mutex, empêchant les lectures fantômes.
- L'état `is_lock` est mis à jour atomiquement sous protection.

#### Monitoring de burnout

Le monitor utilise une communication thread-safe pour lire l'état des coders :

```c
pthread_mutex_lock(&data->coders[i].lock);
last_compile = data->coders[i].last_compile_time;
finish = data->coders[i].has_finished;
pthread_mutex_unlock(&data->coders[i].lock);

// Vérifier le burnout
if (finish == 0 && (get_time() - last_compile > data->time_to_burnout)) {
	// Terminer la simulation
}
```

Chaque coder met à jour `last_compile_time` de manière thread-safe lors de la compilation :

```c
void	compile(t_coder *coder)
{
	print_message(coder->data, coder->number, LOG_COMPILING);
	pthread_mutex_lock(&coder->lock);
	coder->last_compile_time = get_time();  // Mise à jour atomique
	pthread_mutex_unlock(&coder->lock);
	usleep(coder->data->time_to_compile * 1000);
}
```

#### Arrêt sécurisé de la simulation

Quand le monitor détecte un burnout ou la réussite complète, il signale l'arrêt et réveille tous les threads :

```c
pthread_mutex_lock(&data->main_mutex);
data->is_sim_active = 0;  // Signaler l'arrêt
pthread_mutex_unlock(&data->main_mutex);

// Réveiller tous les threads en attente
pthread_mutex_lock(&data->queue_ctrl.mutex);
pthread_cond_broadcast(&data->queue_ctrl.cond);
pthread_mutex_unlock(&data->queue_ctrl.mutex);

pthread_mutex_lock(&data->heap->mutex);
pthread_cond_broadcast(&data->heap->cond);
pthread_mutex_unlock(&data->heap->mutex);
```

Cela garantit qu'aucun thread n'est bloqué indéfiniment lors de l'arrêt.

## Ressources

## Le problème des philosophes

- [Philosophers 42 Guide— “The Dining Philosophers Problem”](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)

### Outils de programmation en C

- [Threads, mutex et programmation concurrente en C](https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/)
- [Heap in C](https://www.geeksforgeeks.org/c/heap-in-c/)
- [Heap in C programming made easy](https://nkugwamarkwilliam.medium.com/heap-in-c-programming-made-easy-e84a8b423660)
- [Manuel linux: timeval](https://man7.org/linux/man-pages/man3/timeval.3type.html)
- [Manuel linux: usleep](https://man7.org/linux/man-pages/man3/usleep.3.html)
- [Manuel linux: pthread_cond](http://manpagesfr.free.fr/man/man3/pthread_cond_init.3.html)

### Visualiseur de codexion

- [Visualiseur de 0xS4cha et 69Nesta](https://codexion-visualizer.sacha-dev.me/)

### Autres projets Codexion

- [Projet de shadox254](https://github.com/shadox254/Codexion)
- [Projet d'Overtekk](https://github.com/Overtekk/Codexion)
- [Projet de 69Nesta](https://github.com/69Nesta/42-Codexion)

### Utilisation de l'IA dans ce projet

1. **Partie programmation**
   - Aide à la correction de certaines erreurs helgrind
   - Aide au debug de certains comportement non correct

3. **Partie documentation**
   - Correction des erreurs d'orthographe et reformulation
   - Aide à la traduction en anglais

## License

Ce projet est sous licence CC0 1.0 Universal (domaine public).

---

**Dernière modification**: 05 avril 2026
**Contact :** alebaron@student.42lehavre.fr
