# Why we chose stuff

# Why SolidJS

SolidJS is faster and easier to write than ReactJS.

Seth later used Svelte + SvelteKit for another personal project and realized it was better.
However, we decided against switching to sveltekit cause nobody wanted to rewrite what we have.

# Why Cesium

Cesium supports the best 3D rendering and 3D tiles.

We considered TurfJS and MapLibreJS but they don’t have the 3D features needed. Mapbox has good 3D features lately but it is paid.

# Why postgres

It works, was used by supabase when we first tried it, have stayed with it since moving to nhost.

# Why GraphQL

We get typing for api responses.

# Why Nhost

We originally setup Supabase realtime, however we realized we had to use supabase’s own JS library to make subscription queries and their graphql library didn’t support subscriptions yet. So, we decided to add hasura to the stack with postgres, but then we ran into auth issues as we couldn’t specify who could access specific rows with Hasura. That’s when we found NHost and moved to that (it integrates auth with Hasura)