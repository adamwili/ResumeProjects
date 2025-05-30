#!/bin/bash
set -e

# Wait for MySQL to be ready
until nc -z "$MYSQL_HOST" "$MYSQL_PORT"; do
  echo "Waiting for MySQL..."
  # Print the current DJANGO_ENV
  echo "Current DJANGO_ENV: $DJANGO_ENV"
  sleep 4
done

# Run Django setup commands
python manage.py migrate --no-input
python manage.py tailwind install --no-input
python manage.py tailwind build --no-input
python manage.py collectstatic --no-input
python create_super.py --username "$DJANGO_SUPERUSER_USERNAME" --email "$DJANGO_SUPERUSER_EMAIL"



exec "$@"