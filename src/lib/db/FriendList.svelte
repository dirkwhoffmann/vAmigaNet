<script>
	import { liveQuery } from 'dexie';
	import { db } from './db';
	import { browser } from '$app/environment';

	let friends = liveQuery(() => (browser ? db.friends.toArray() : []));
</script>

<ul>
	{#if $friends}
		{#each $friends as friend (friend.id)}
			<li>{friend.name}, {friend.age}</li>
		{/each}
	{/if}
</ul>
