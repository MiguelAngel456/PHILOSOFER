# 🤔 Philosopher

## Descripción

**Philosopher** es un proyecto de la escuela 42 que implementa la clásica problemática de los filósofos comensales. El objetivo es gestionar la concurrencia y evitar condiciones de carrera y deadlocks usando procesos o threads, sincronizando mediante semáforos o mutex.

Este proyecto fue desarrollado y probado en Linux.

---

## Tecnologías

- Lenguaje: C  
- Sistema operativo: Linux  
- Uso de procesos o threads, sincronización con semáforos/mutex.

---

## Instalación y uso

1. Clona el repositorio:
   ```bash
   git clone https://github.com/tu_usuario/philosopher.git
   cd philosopher

2. Compilar el repositorio:
   ```bash
   make

3. Ejecutar el proyecto:
   ```bash
   ./philosopher number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

   - `number_of_philosophers`: cantidad de filósofos  
   - `time_to_die`: tiempo en milisegundos antes de que un filósofo muera sin comer  
   - `time_to_eat`: tiempo que un filósofo tarda en comer  
   - `time_to_sleep`: tiempo que un filósofo tarda en dormir  
   - `[number_of_times_each_philosopher_must_eat]`: (opcional) número de veces que cada filósofo debe comer antes de que el programa termine
