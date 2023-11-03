<template>
  <h1>
    <a :href="link" target="_blank">{{ name }}</a>
  </h1>
</template>

<script lang="ts">
import { defineComponent } from "vue";

export default defineComponent({
  name: "SortHeader",
  props: {
    name: {
      type: String,
      required: true,
    },
    link: {
      type: String,
      required: true,
    },
  },
});
</script>

<style>
a {
  color: rgb(var(--v-theme-primary));
  text-decoration: none;
}

a:hover {
  text-decoration: underline;
}

a:active {
  color: rgb(var(--v-theme-info));
  text-decoration: underline;
}
</style>
