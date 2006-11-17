<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">

  <!-- nastaveni jazyka (defaultne cz) -->
  <xsl:variable name="lng">en</xsl:variable>


  <xsl:template match="/active_list">

    <dialog_data>
      <attributes>
        <attribute name="id" label="id" />

        <xsl:choose>

          <!-- english -->
          <xsl:when test="$lng='en'">
            <attribute name="db_name" label="Database" />
            <attribute name="matrix_name" label="Data matrix" />
            <attribute name="task_name" label="Task name" />
            <attribute name="task_type" label="Task type" />
            <attribute name="gen_state" label="State" />
            <attribute name="gen_total_time" label="Total time" />
            <attribute name="gen_start_time" label="Start time" />
            <attribute name="num_hyp" label="Hypotheses count" />
            <attribute name="num_tests" label="Number of verifications" />
          </xsl:when>

          <!-- cesky-->
          <xsl:when test="$lng='cz'">
            <attribute name="db_name" label="Datab�ze" />
            <attribute name="matrix_name" label="Datov� matice" />
            <attribute name="task_name" label="Jm�no �lohy" />
            <attribute name="task_type" label="Typ �lohy" />
            <attribute name="gen_state" label="Stav" />
            <attribute name="gen_total_time" label="Celkov� �as" />
            <attribute name="gen_start_time" label="Za��tek testu" />
            <attribute name="num_hyp" label="Po�et hypot�z" />
            <attribute name="num_tests" label="Po�et verifikac�" />
          </xsl:when>
        </xsl:choose>

        <!-- vychozi hodnoty:
                numeric_sort="false"
                default_sort_direction="ascending"     -->

      </attributes>

      <values>
        <xsl:apply-templates select="task" mode="values"/>
      </values>

    </dialog_data>

  </xsl:template>



	<!-- vypise hodnoty -->
	<xsl:template match="node()" mode="values">		
		

		<xsl:text disable-output-escaping="yes">
		&lt;value </xsl:text>
		<xsl:apply-templates select="@*" mode="values"/>

		<xsl:text disable-output-escaping="yes">/&gt;</xsl:text>


	</xsl:template>



	<!-- naplni hodnotu pro categories -->
	<xsl:template match="ctgr" mode="values">
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no">; </xsl:text>
		</xsl:if>

		<xsl:value-of select="@name"/>
		<xsl:text disable-output-escaping="no"> (</xsl:text>
		<xsl:value-of select="@freq"/>
		<xsl:text disable-output-escaping="no">)</xsl:text>
	</xsl:template>



	



	<!-- naplni hodnotu -->
	<xsl:template match="@*" mode="values">
	
		<xsl:value-of select="name()"/>
		
		<xsl:text disable-output-escaping="yes">="</xsl:text>
	
		<xsl:value-of select="."/>

		<xsl:text disable-output-escaping="yes">" </xsl:text>

	</xsl:template>

	



</xsl:stylesheet>
