
/* allocate a new target */
/* error checking done by caller! */
poison_target_t *poison_new_target(void)
{
	poison_target_t *node;

	node = malloc(sizeof(poison_target_t));

	if (node)
	{
		memset((char *)node, 0, sizeof(node));
	}

	return node;
}

int poison_register_trigger(poison_session_t *session, poison_strategy_t strategy, poison_target_t *target)
{
	poison_target_t *node;
		
	/* if there exists no targets yet */
	if (!session->targets)
	{
		/* very first target */	
		node = poison_new_target();

		if (!node)
		{
			strcpy(session->errbuf, "out of memory");
			return POISON_NOMEM;	
		}
		
		memcpy(node, target, sizeof(poison_target_t));

		node->strategy = strategy;

		session->targets = node;

		if (session->triggers)
		{
			/* state corruption. this should never happen */
			return POISON_CORRUPT;
		}

		session->triggers = poison_new_target();

		if (!session->triggers)
		{
			strcpy(session->errbuf, "out of memory");
			return POISON_NOMEM;	
		}

		memcpy(session->triggers, node, sizeof(poison_target_t));
	
		return POISON_OK;
	}

	/* if there exists targets, but no triggers */
	if (!session->triggers)
	{
		session->triggers = poison_new_target();

		if (!session->triggers)
		{
			strcpy(session->errbuf, "out of memory");
			return POISON_NOMEM;	
		}

		node = session->triggers;

		memcpy(node, target, sizeof(poison_target_t));
		node->strategy = strategy;

		return POISON_OK;
	}

	/* if target is not on global target list, add it */

	node = session->targets;

	while (node)
	{
		
	}

	
	/* target is not on trigger list already, add it */

	

}

/* free target list */
void poison_free_targets(poison_target_t *list)
{
	poison_target_t *cur;
	poison_target_t *next;

	cur = list;

	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}

	return;
}