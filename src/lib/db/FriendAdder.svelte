<script>
  import { db } from "./db";
  import MyButton from '$lib/widgets/MyButton.svelte';

  export let defaultAge = 21;

  let status = "";

  let friendName = "";
  let friendAge = defaultAge;

  async function addFriend() {
    try {

      // Add the new friend!
      const id = await db.friends.add({
        name: friendName,
        age: friendAge
      });

      status = `Item ${friendName} successfully added with id ${id}`;
      
      // Reset form:
      friendName = "";
      friendAge = defaultAge;
    } catch (error) {
      status = `Failed to add ${friendName}: ${error}`;
    }
  }
</script>
<div class="text-red-500">
  <p>{status}</p>
  <fieldset>
    <!--<legend>Add new friend</legend>-->
    <label>
      Name:
      <input
          type="text"
          bind:value={friendName} />
    </label>
    <br/>
    <label>
      Age:
      <input
        type="number"
        bind:value={friendAge} />
    </label>
    <br />
    <MyButton on:click={addFriend} label = "Add item"></MyButton>
  </fieldset>
</div>